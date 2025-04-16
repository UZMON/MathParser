#pragma once
#include "MathParser.h"

void ParseMathTokens(Token* tokens, size_t tokensCount)
{
	for (size_t i = 0; i < tokensCount; i++)
	{
		Token currentToken = tokens[i];

	} 
}

ASTNode* CreateValueNode(ASTNodeType nodeType, const char* valuePtr, size_t valuelength)
{
	return NULL;
}

//  1212 + ( 232 - 332)
//  1212
// + 
// (
// 232
// -
// 332
// )
