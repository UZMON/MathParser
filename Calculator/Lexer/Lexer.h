#pragma once
#include <stddef.h>
#include "../LexerParserShared/Token.h"
#include "../LexerParserShared/Position.h"
#include "SymbolBlock.h"

void InitLexer ( );

/// <summary>
/// Lexes data into TokenArray 
/// </summary>
/// <param name="dataPtr">Pointer to the null-terminated input string.</param>
/// <param name="outTokens">Tokens array (of size MAX_EXPRESSION_SIZE ) ; parsed Tokens are copied to this array.</param>
/// <param name="outCount">Count of symbolblocks found will be outputed to this.</param>
/// <param name="error">If error occurs during run , the value of error will be 1 ; otherwise 0.</param>
void Lex(char* dataPtr, Token* outTokens, size_t* outCount, int* error);

/// <summary>
/// Reads all Tokens found in symbolBlockArr and outputs them to outTokens and their count to outCount .
/// </summary>
/// <param name="symbolBlockArr">The array containing SymboBlocks which are going to be converted into Tokens.</param>
/// <param name="outTokens">Tokens array (of size MAX_EXPRESSION_SIZE ) ; parsed Tokens are copied to this array.</param>
/// <param name="outCount">Count of symbolblocks found will be outputed to this.</param>
/// <param name="error">If error occurs during run , the value of error will be 1 ; otherwise 0.</param>
int ReadTokens(SymbolBlockArr symbolBlockArr, Token* outTokens, size_t* outCount);