#include "ASTPool.h"

ASTNode* CreateValueNode(ASTPool* astPool, ASTNodeType nodeType, const char* valuePtr, size_t valueLength)
{
	ASTNode* node = &astPool->nodes[astPool->currentIndex++];
	node->nodeType = nodeType;
	node->value.valuePtr = valuePtr;
	node->value.length = valueLength;
	return node;
}

ASTNode* CreateOperatorNode(ASTPool* astPool, ASTNodeType nodeType, const ASTNode* left, const ASTNode* right)
{
	ASTNode* node = &astPool->nodes[astPool->currentIndex++];
	node->nodeType = nodeType;
	node->op.left = left;
	node->op.right = right;
	return node;
}