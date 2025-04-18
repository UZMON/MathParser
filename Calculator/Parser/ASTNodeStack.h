#pragma once
#include "ASTNode.h"
#include "ASTPool.h"
#include "../Constants.h"

// A stack structure for managing ASTNode pointers in LIFO(Last-In, First-Out) order.
typedef struct ASTNodeStack ASTNodeStack;
struct ASTNodeStack
{
	ASTNode* ASTNodes[ MAX_AST_NODES_STACK ];
	size_t nextIndex;
};

// Returns 0 on success, or 1 on error (e.g., if the stack is full).
int PushASTNodes(ASTNodeStack* stack, int count, ...);

// Returns 0 on success, or 1 on error (e.g., if the stack is full).
int PushASTNode ( ASTNodeStack* stack , ASTNode* node );

// Creates a new node within the AST pool, pushes the newly created node to the stack,
// then calls ReduceTheStack to reduce the stack if possible.
// Returns 0 on success, or 1 on error (e.g., if the stack is full).
int EmitNode ( ASTPool* astPool ,ASTNodeStack* stack , ASTNodeType nodeType , Position position , int expressionDepth );

int EmitTerminalNode ( ASTPool* astPool , ASTNodeStack* stack , int expressionDepth );

//Returns the ASTNodePtr , or NULL if the stack is empty.
ASTNode* PopASTStack ( ASTNodeStack* stack );
//Returns the ASTNode Ptr , or NULL if the stack is empty.
ASTNode* PeekASTStack ( ASTNodeStack* stack );

int ReduceTheStack ( ASTNodeStack* AST_Stack );