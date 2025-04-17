#pragma once
#include "ASTNode.h"


// Priority(leftValue) > Priority(rightValue)
//Returns 1 for true , 0 for false
int Priority_MoreThan ( ASTNodeType leftValue , ASTNodeType rightValue );

// Priority(leftValue) < Priority(rightValue)
//Returns 1 for true , 0 for false
int Priority_LessThan ( ASTNodeType leftValue , ASTNodeType rightValue );

// Priority(leftValue) == Priority(rightValue)
//Returns 1 for true , 0 for false
int Priority_Equal ( ASTNodeType leftValue , ASTNodeType rightValue );

// Priority(leftValue) >= Priority(rightValue)
//Returns 1 for true , 0 for false
int Priority_MoreThanOrEqual ( ASTNodeType leftValue , ASTNodeType rightValue );

// Priority(leftValue) <= Priority(rightValue)
//Returns 1 for true , 0 for false
int Priority_LessThanOrEqual ( ASTNodeType leftValue , ASTNodeType rightValue );