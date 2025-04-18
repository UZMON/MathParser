#pragma once
#include "ASTNode.h"


// Priority(a) > Priority(b)
//Returns 1 for true , 0 for false
int HasHigherPriority ( ASTNode* a , ASTNode* b );

// Priority(a) < Priority(b)
//Returns 1 for true , 0 for false
int HasLowerPriority ( ASTNode* a , ASTNode* b );

// Priority(a) == Priority(b)
//Returns 1 for true , 0 for false
int HasEqualPriority ( ASTNode* a , ASTNode* b );

// Priority(a) >= Priority(b)
//Returns 1 for true , 0 for false
int HasHigherOrEqualPriority ( ASTNode* a , ASTNode* b );

// Priority(a) <= Priority(b)
//Returns 1 for true , 0 for false
int HasLowerOrEqualPriority ( ASTNode* a , ASTNode* b );