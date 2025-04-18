#pragma once
#include "ASTNodeStack.h"
#include "../LexerParserShared/Token.h"

// TokenHandler is a function that processes a token and modifies the AST accordingly.
// Returns 0 on success, or 1 if an error occurs.
typedef int (*TokenHandler)(ASTPool*, ASTNodeStack*, TokenArray tokenArr, size_t* currentIndex, int* expressionDepth);

// Maps every Token category to its corresponding handler function.
const TokenHandler tokenHandlerTable[TokenTypeCategory_Count];
const TokenHandler GetTokenHandler(TokenTypeCategory category);

// Each handler uses it's own logic to handle different categories of tokens

int HandleValue(ASTPool* AST_Pool, ASTNodeStack* AST_Stack, TokenArray tokenArr, size_t* currentIndex, int* expressionDepth);
int HandleBracket(ASTPool* AST_Pool, ASTNodeStack* AST_Stack, TokenArray tokenArr, size_t* currentIndex, int* expressionDepth);