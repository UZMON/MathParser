#include "ASTNodeStack.h"
#include "../Utils/ErrorPrinter.h"
#include "../Utils/Macros.h"
#include "Priority.h"
#include <stdarg.h>

int PushASTNodes(ASTNodeStack* stack, int count, ...)
{
    if (stack->nextIndex + count > MAX_AST_NODES_STACK) {
        PrintErrorf("StackOverFlow: Cannot push %d more nodes (max %d).", count, MAX_AST_NODES_STACK); // @Error[ASTNodeStack].
        return 1;
    }
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        ASTNode* node = va_arg(args, ASTNode*);
        if (!node) {
            PrintErrorf("Internal error: attempted to push a NULL node onto the AST stack"); // @Error[ASTNodeStack].
            va_end(args);
            return 1;
        }
        stack->ASTNodes[stack->nextIndex++] = node;
    }
    va_end(args);
    return 0;
}

int PushASTNode(ASTNodeStack* stack, ASTNode* node)
{
    if (!node) {
        PrintErrorf("Internal error: attempted to push a NULL node onto the AST stack"); // @Error[ASTNodeStack].
        return 1;
    }
    if (stack->nextIndex >= MAX_AST_NODES_STACK) {
        PrintErrorf("StackOverFlow : ASTNodes Stack exceeds the Maximum %d", MAX_AST_NODES_STACK); // @Error[ASTNodeStack].
        return 1;
    }
    stack->ASTNodes[stack->nextIndex++] = node;
    return 0;
}

int EmitNode(ASTPool* astPool, ASTNodeStack* stack, ASTNodeType nodeType, Position position, int expressionDepth)
{
    ASTNode* currentNode = CreateNode(astPool, nodeType, position, expressionDepth);
    if (!currentNode) {
        return 1; //Error
    }
    if (!PushASTNode(stack, currentNode)) {
        return ReduceTheStack(astPool, stack, expressionDepth);
    }
    return 1; //Error
}

int EmitTerminalNode(ASTPool* astPool, ASTNodeStack* stack, int expressionDepth)
{
    Position noPosition = { -1, -1 };

    if (expressionDepth != 0) {
        PrintErrorf("Mismatched parentheses: expected depth 0 but got %d", expressionDepth); //@Error[ASTNodeStack].
        return 1;
    }

    int error = EmitNode(astPool, stack, EndOfNodesNodeType, noPosition, expressionDepth);
    if (error)
        return error;

    if (stack->nextIndex != 1) {
        PrintErrorf("Unexpected end of expression: incomplete expression (missing operand)"); //@Error[ASTNodeStack].
        return 1;
    }
    return 0;
}

ASTNode* PopASTStack(ASTNodeStack* stack)
{
    if (stack->nextIndex == 0) {
        return NULL;
    }
    return stack->ASTNodes[--stack->nextIndex];
}

ASTNode* PeekASTStack(ASTNodeStack* stack)
{
    if (stack->nextIndex == 0) {
        return NULL;
    }
    return stack->ASTNodes[stack->nextIndex - 1];
}

int ReduceTheStack(ASTPool* astPool, ASTNodeStack* AST_Stack, int expressionDepth)
{
    // Each step that returns 2 shrinks the stack by one node, so it can never
    // take more than MAX_AST_NODES_STACK steps to settle.
    for (size_t iterations = 0; iterations <= MAX_AST_NODES_STACK; iterations++) {
        int result = ReduceTheStack_OneStep(astPool, AST_Stack, expressionDepth);
        if (result != 2)
            return result;
    }
    PrintErrorf("Internal error: stack reduction exceeded maximum iterations (%d)", MAX_AST_NODES_STACK); // @Error[ASTNodeStack].
    return 1;
}

// A binary node is only a valid operand once both its children are attached ;
// while it's still waiting on one of them it can't be handed off as someone
// else's operand (that would bury the gap where it can never be filled in).
static int IsNodeComplete(ASTNode* node)
{
    if (GetNodeCategory(node->nodeType) != BinaryNodeCategory) {
        return 1; // Value/None nodes are leaves ; always complete.
    }
    return node->binary.leftChild != NULL && node->binary.rightChild != NULL;
}

//  Note :
// It is obligatory by this logic that any node inside the stack ( other than the top node !! ) closer to the topNode will always have higher priority than the ones far away
// Return 0 for success , 1 for error , 2  if the stack might still be reducable.
static int ReduceTheStack_OneStep(ASTPool* astPool, ASTNodeStack* AST_Stack, int expressionDepth)
{
    ASTNode* topNode = PopASTStack(AST_Stack);
    ASTNode* secondNode = PopASTStack(AST_Stack);
    ASTNode* thirdNode = PeekASTStack(AST_Stack); // Don't pop this yet.
    // Case 1: topNode has no valid operand at its own depth ; either the stack
    // is genuinely empty, whatever's underneath belongs to an outer/shallower
    // scope (e.g. topNode is a unary operator right after "(" or another operator),
    // or it's an operator still waiting on its own operand and so isn't ready
    // to be attached anywhere yet.
    if (!Exists(secondNode) || secondNode->expressionDepth < topNode->expressionDepth || !IsNodeComplete(secondNode)) {
        if (Exists(secondNode)) {
            if (PushASTNode(AST_Stack, secondNode))
                return 1;
        }
        return StackEmptyCase(astPool, AST_Stack, topNode, expressionDepth);
    }
    // Case 2: thirdNode exists and has higher or equal priority than topNode
    if (Exists(thirdNode) && HasHigherOrEqualPriority(thirdNode, topNode)) { // P(third) >= P(top)
        if (!isRightAttachable(thirdNode->nodeType)) {
            PrintErrorf("Unexpected token at line %zu, column %zu: values must be separated by an operator", secondNode->position.line, secondNode->position.column); // @Error[ASTNodeStack].
            return 1;
        }
        thirdNode->binary.rightChild = secondNode;
        if (PushASTNode(AST_Stack, topNode))
            return 1;
        return 2; // We jump back to reduce further since the stack may allow more reductions.
    }
    // Case 3: secondNode has higher or equal priority than topNode
    if (HasHigherOrEqualPriority(secondNode, topNode)) { // P(second) >= P(top)
        return AttachSecondNodeToTopNode(AST_Stack, topNode, secondNode);
    }
    // Case 4: Cannot reduce any further.
    return PushASTNodes(AST_Stack, 2, secondNode, topNode);
}

static int StackEmptyCase(ASTPool* astPool, ASTNodeStack* AST_Stack, ASTNode* topNode,int expressionDepth)
{
    if (isLeftAttachable(topNode->nodeType) && topNode->binary.leftChild == NULL) {
        if (!isUnaryCapable(topNode->nodeType)) {
            PrintErrorf("Unexpected operator '%s' at line %zu, column %zu: missing left operand", GetNodeName(topNode->nodeType), topNode->position.line, topNode->position.column); // @Error[ASTNodeStack].
            return 1;
        }
        ASTNode* noneNode = CreateNoneNode(astPool, expressionDepth);
        if (!noneNode) {
            return 1;
        }
        topNode->binary.leftChild = noneNode;
    }
    return PushASTNode(AST_Stack, topNode); // Nothing to reduce; push back topNode.
}

static int AttachSecondNodeToTopNode(ASTNodeStack* AST_Stack, ASTNode* topNode, ASTNode* secondNode)
{
    if (topNode->nodeType == EndOfNodesNodeType)
        return PushASTNode(AST_Stack, secondNode); // If the topNode is the endNode we remove it from stack , and we keep second node.
    if (!isLeftAttachable(topNode->nodeType)) {
        PrintErrorf("Unexpected token at line %zu, column %zu: values must be separated by an operator", topNode->position.line, topNode->position.column); // @Error[ASTNodeStack].
        return 1;
    }
    topNode->binary.leftChild = secondNode;
    return PushASTNode(AST_Stack, topNode);
}