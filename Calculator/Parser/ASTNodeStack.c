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
        stack->ASTNodes[stack->nextIndex++] = node;
    }
    va_end(args);
    return 0;
}

int PushASTNode(ASTNodeStack* stack, ASTNode* node)
{
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
    
    return EmitNode(astPool, stack, EndOfNodesNodeType, noPosition, expressionDepth);
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
    while (true) { // Keep reducing until no more reductions are possible
        int result = ReduceTheStack_OneStep(astPool, AST_Stack, expressionDepth);
        if (result != 2)
            return result;
    }
}

//  Note :
// It is obligatory by this logic that any node inside the stack ( other than the top node !! ) closer to the topNode will always have higher priority than the ones far away
// Return 0 for success , 1 for error , 2  if the stack might still be reducable.
static int ReduceTheStack_OneStep(ASTPool* astPool, ASTNodeStack* AST_Stack, int expressionDepth)
{
    ASTNode* topNode = PopASTStack(AST_Stack);
    ASTNode* secondNode = PopASTStack(AST_Stack);
    ASTNode* thirdNode = PeekASTStack(AST_Stack); // Don't pop this yet.
    // Case 1: Stack only contains topNode
    if (!Exists(secondNode)) {
        return StackEmptyCase(astPool, AST_Stack, topNode, expressionDepth);
    }
    // Case 2: thirdNode exists and has higher or equal priority than topNode
    if (Exists(thirdNode) && HasHigherOrEqualPriority(thirdNode, topNode)) { // P(third) >= P(top)
        thirdNode->binary.rightChild = secondNode;
        PushASTNode(AST_Stack, topNode);
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
        topNode->binary.leftChild = CreateNoneNode(astPool, expressionDepth);
    }
    return PushASTNode(AST_Stack, topNode); // Nothing to reduce; push back topNode.
}

static int AttachSecondNodeToTopNode(ASTNodeStack* AST_Stack, ASTNode* topNode, ASTNode* secondNode)
{
    if (topNode->nodeType == EndOfNodesNodeType)
        return PushASTNode(AST_Stack, secondNode); // If the topNode is the endNode we remove it from stack , and we keep second node.
    topNode->binary.leftChild = secondNode;
    return PushASTNode(AST_Stack, topNode);
}