#pragma once
#include "ASTNode.h"
#include "../Constants.h"

// A stack structure for managing ASTNode pointers in LIFO(Last-In, First-Out) order.
typedef struct ASTNodeStack ASTNodeStack;
struct ASTNodeStack
{
	ASTNode* ASTNodes[ MAX_AST_NODES_STACK ];
	size_t lastIndex;
};

void InitASTNodeStack ( ASTNodeStack* stack );
int PushASTNode ( ASTNodeStack* stack , ASTNode* node );
ASTNode* PopASTNode ( ASTNodeStack* stack );