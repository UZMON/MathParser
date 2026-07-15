#include "ASTPool.h"
#include "../Utils/ErrorPrinter.h"

ASTNode* CreateNode(ASTPool* astPool, ASTNodeType nodeType, Position position, int expressionDepth)
{
    if (astPool->currentIndex >= MAX_AST_NODES) {
        PrintErrorf("Expression too complex: exceeded maximum of %d AST nodes at line %zu, column %zu", MAX_AST_NODES, position.line, position.column); // @Error[ASTPool].
        return NULL;
    }
    ASTNode* node = &astPool->nodes[astPool->currentIndex++];
    node->nodeType = nodeType;
    node->position = position;
    node->expressionDepth = expressionDepth;
    return node;
}

ASTNode* CreateValueNode(ASTPool* astPool, ASTNodeType nodeType, const char* valuePtr, size_t valueLength, Position position, int expressionDepth)
{
    if (astPool->currentIndex >= MAX_AST_NODES) {
        PrintErrorf("Expression too complex: exceeded maximum of %d AST nodes at line %zu, column %zu", MAX_AST_NODES, position.line, position.column); // @Error[ASTPool].
        return NULL;
    }
    ASTNode* node = &astPool->nodes[astPool->currentIndex++];
    node->nodeType = nodeType;
    node->value.valuePtr = valuePtr;
    node->value.length = valueLength;
    node->position = position;
    node->expressionDepth = expressionDepth;
    return node;
}

ASTNode* CreateNoneNode(ASTPool* astPool, int expressionDepth)
{
    if (astPool->currentIndex >= MAX_AST_NODES) {
        PrintErrorf("Expression too complex: exceeded maximum of %d AST nodes", MAX_AST_NODES); // @Error[ASTPool].
        return NULL;
    }
    ASTNode* node = &astPool->nodes[astPool->currentIndex++];
    node->nodeType = NoneNodeType;
    node->expressionDepth = expressionDepth;
    return node;
}
