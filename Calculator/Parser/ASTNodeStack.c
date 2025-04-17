#include "ASTNodeStack.h"
#include "../Utils/ErrorPrinter.h"
#include "Priority.h"

void InitASTNodeStack(ASTNodeStack* stack)
{
	stack->lastIndex = 0;
}

int PushASTNode(ASTNodeStack* stack, ASTNode* node)
{
	if (stack->lastIndex >= MAX_AST_NODES_STACK)
	{
		// @ERROR[ASTNodeStack]: StackOverFlow.
		PrintErrorf("StackOverFlow : ASTNodes Stack exceeds the Maximum %d", MAX_AST_NODES_STACK);
		return 1;
	}
	stack->ASTNodes[stack->lastIndex++] = node;
	 return 0;
}

ASTNode* PopASTStack(ASTNodeStack* stack)
{
	if (stack->lastIndex == 0)
	{
		return NULL;
	}
	return stack->ASTNodes[-- stack->lastIndex ];
}

ASTNode* PeekASTStack(ASTNodeStack* stack)
{
	if (stack->lastIndex == 0)
	{
		return NULL;
	}
	return stack->ASTNodes[stack->lastIndex - 1];
}

int ReduceTheStack(ASTNodeStack* AST_Stack)
{
	ASTNode* topNode = NULL;
	ASTNode* secondNode = NULL;
	ASTNode* thirdNode = NULL;

start:
	topNode = PopASTStack(AST_Stack);
	secondNode = PopASTStack(AST_Stack);
	thirdNode = PeekASTStack(AST_Stack); // Don't pop this yet.

	// Case 1: Stack only contains topNode
	if (!Exists(secondNode))
	{
		if (isLeftAttachable(topNode->nodeType) && topNode->binary.leftChild == NULL)
		{
			// @Error[ASTNodeStack]: Expected a left value for the operator.
			PrintErrorf("Expected a left value for the operator at ( %d, %d )", topNode->position.line, topNode->position.column);
			return 1;
		}
		// Nothing else to reduce; push back topNode.
		PushASTNode(AST_Stack, topNode);
		return 0;
	}

	// Case 2: thirdNode exists and has higher or equal priority than topNode
	if (Exists(thirdNode) && Priority_MoreThanOrEqual(thirdNode->nodeType, topNode->nodeType)) // P(third) >= P(top)
	{
		thirdNode->binary.rightChild = secondNode;
		PushASTNode(AST_Stack, topNode);
		// We jump back to reduce further since the stack may allow more reductions.
		goto start;
	}

	// Case 3: secondNode has higher or equal priority than topNode
	if (Priority_MoreThanOrEqual(secondNode->nodeType, topNode->nodeType)) // P(second) >= P(top)
	{
		topNode->binary.leftChild = secondNode;
		PushASTNode(AST_Stack, topNode);
		return 0;
	}

	// Case 4: Cannot reduce any further.
	PushASTNode(AST_Stack, secondNode);
	PushASTNode(AST_Stack, topNode);
	return 0;
}