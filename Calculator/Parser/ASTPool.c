#include "ASTPool.h"

ASTNode* CreateValueNode(ASTPool* astPool, ASTNodeType nodeType, const char* valuePtr, size_t valueLength, Position position)
{
	ASTNode* node = &astPool->nodes[astPool->currentIndex++];
	node->nodeType = nodeType;
	node->value.valuePtr = valuePtr;
	node->value.length = valueLength;
	node->position = position;
	return node;
}

ASTNode* CreateOperatorNode(ASTPool* astPool, ASTNodeType nodeType, const ASTNode* left, const ASTNode* right, Position position)
{
	ASTNode* node = &astPool->nodes[astPool->currentIndex++];
	node->nodeType = nodeType;
	node->binary.leftChild = left;
	node->binary.rightChild = right;
	node->position = position;
	return node;
}