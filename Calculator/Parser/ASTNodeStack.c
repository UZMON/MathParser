#include "ASTNodeStack.h"
#include "../Utils/ErrorPrinter.h"

void InitASTNodeStack(ASTNodeStack* stack)
{
	stack->lastIndex = 0;
}

int PushASTNode(ASTNodeStack* stack, ASTNode* node)
{
	if (stack->lastIndex >= MAX_AST_NODES_STACK)
	{
		PrintErrorf("StackOverFlow : ASTNodes Stack exceeds the Maximum %d", MAX_AST_NODES_STACK);
		return 0;
	}
	stack->ASTNodes[stack->lastIndex++] = node;
	 return 1;
}

ASTNode* PopASTNode(ASTNodeStack* stack)
{
	if (stack->lastIndex == 0)
	{
		PrintErrorf("StackUnderFlow : Trying to pop an empty ASTNodeStack");
		return NULL;
	}
	return stack->ASTNodes[-- stack->lastIndex ];
}
