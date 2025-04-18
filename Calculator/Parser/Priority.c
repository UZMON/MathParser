#include "Priority.h"

int HasHigherPriority(ASTNode* a, ASTNode* b)
{
    // Nodes with higher expression depth have higher priority.
    int hasDeeperNesting = a->expressionDepth > b->expressionDepth;

    // At the same depth, nodes with lower precedence value bind tighter => Higher priority.
    int hasTighterBinding = GetNodePrecedence(a->nodeType) < GetNodePrecedence(b->nodeType);

    return hasDeeperNesting || (a->expressionDepth == b->expressionDepth && hasTighterBinding);
}

int HasLowerPriority(ASTNode* a, ASTNode* b)
{
    // Nodes with lower expression depth have lower priority.
    int isShallower = a->expressionDepth < b->expressionDepth;

    // At the same depth, nodes with higher precedence value bind looser => lower priority.
    int bindsLooser = GetNodePrecedence(a->nodeType) > GetNodePrecedence(b->nodeType);

    return isShallower || (a->expressionDepth == b->expressionDepth && bindsLooser);
}

int HasEqualPriority(ASTNode* a, ASTNode* b)
{
    return (a->expressionDepth == b->expressionDepth) && (GetNodePrecedence(a->nodeType) == GetNodePrecedence(b->nodeType));
}

int HasHigherOrEqualPriority(ASTNode* a, ASTNode* b)
{
    return HasHigherPriority(a, b) || HasEqualPriority(a, b);
}

int HasLowerOrEqualPriority(ASTNode* a, ASTNode* b)
{
    return HasLowerPriority(a, b) || HasEqualPriority(a, b);
}