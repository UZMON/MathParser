#pragma once
#include <stddef.h>
#include "../LexerParserShared/Token.h"
#include "SymbolBlock.h"

/// <summary>
/// Lexes data into TokenArray 
/// </summary>
/// <param name="dataPtr">Pointer to the null-terminated input string.</param>
/// <param name="outTokens">Tokens array (of size MAX_EXPRESSION_SIZE ) ; parsed Tokens are copied to this array.</param>
/// <param name="outCount">Count of symbolblocks found will be outputed to this.</param>
/// <param name="error">If error occurs during run , the value of error will be 1 ; otherwise 0.</param>
void Lex(char* dataPtr, Token* outTokens, size_t* outCount, int* error);

/// <summary>
/// Reads all SymbolBlocks found in the input string.
/// </summary>
/// <param name="dataPtr">Pointer to the null-terminated input string.</param>
/// <param name="outSymbolBlocks">SymbolBlock array (of size MAX_EXPRESSION_SIZE ) ; parsed blocks are copied to this array.</param>
/// <param name="outCount">Pointer to the count of symbolblocks found.</param>
void ReadSymbolBlocks(const char* dataPtr, SymbolBlock* outSymbolBlocks, size_t* outCount);

/// <summary>
/// Reads all Tokens found in symbolBlockArr and outputs them to outTokens and their count to outCount .
/// </summary>
/// <param name="symbolBlockArr">The array containing SymboBlocks which are going to be converted into Tokens.</param>
/// <param name="outTokens">Tokens array (of size MAX_EXPRESSION_SIZE ) ; parsed Tokens are copied to this array.</param>
/// <param name="outCount">Count of symbolblocks found will be outputed to this.</param>
/// <param name="error">If error occurs during run , the value of error will be 1 ; otherwise 0.</param>
void ReadTokens(const SymbolBlock* symbolBlocks,size_t symbolBlocksCount, Token* outTokens, size_t* outCount, int* error);
