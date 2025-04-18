#include "ASTPool.h"

ASTNode* CreateNode(ASTPool* astPool, ASTNodeType nodeType, Position position, int expressionDepth)
{
    ASTNode* node = &astPool->nodes[astPool->currentIndex++];
    node->nodeType = nodeType;
    node->position = position;
    node->expressionDepth = expressionDepth;
    return node;
}

ASTNode* CreateValueNode(ASTPool* astPool, ASTNodeType nodeType, const char* valuePtr, size_t valueLength, Position position, int expressionDepth)
{
    ASTNode* node = &astPool->nodes[astPool->currentIndex++];
    node->nodeType = nodeType;
    node->value.valuePtr = valuePtr;
    node->value.length = valueLength;
    node->position = position;
    node->expressionDepth = expressionDepth;
    return node;
}