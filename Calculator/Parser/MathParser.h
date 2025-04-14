#pragma once
#include <stddef.h>
#include "../LexerParserShared/Token.h"
#include "../Constants.h"

#define MAX_AST_NODES MAX_EXPRESSION_SIZE

//Node Types used in the Abstract Syntax Tree
typedef enum
{
	// Value types
	Value_Float,
	Value_Integer,

	//Operators
	Op_Addition,
	Op_Subtraction,
	Op_Multiplication,
	Op_Division,
	Op_Remainder
}ASTNodeType;

//The node struct , in which the AST will be composed of it.
typedef struct
{
	ASTNodeType nodeType;
	ASTNode* left;
	ASTNode* right;
	union
	{
		//For Value Node Types
		struct {
			const char* valuePtr;
			const size_t length;
		} value;
	};
}ASTNode;

void ParseMathTokens ( Token* tokens , size_t tokensCount );

ASTNode* CreateValueNode ( ASTNodeType nodeType , const char* valuePtr , size_t valuelength );