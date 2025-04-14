#pragma once
#include <stddef.h>
#include "../LexerParserShared/Token.h"

#define SYMBOL_TABLE_SIZE 128
// NOTE: You may want to adjust SYMBOL_TABLE_SIZE based on the highest Unicode value
// used in any of the character sets below.
//
// Each SYMBOL is defined using the following parameters:
// SYMBOL(
//     SymbolName,               // A unique name for the symbol
//     CharacterSet,             // A string of characters that this symbol matches
//     MaxLength,                // Maximum length for a block of consecutive matching symbols
//     TokenType                 // Token it maps to; use SpecialSymbolToken if it is handled specially in ReadTokens() of Lexer.c
// )
#define SymbolsList \
	SYMBOL(UnknownSymbol, "",1,SpecialSymbolToken) \
	SYMBOL(DigitSymbol, "0123456789",100,SpecialSymbolToken) \
	SYMBOL(DotSymbol, ".",1,SpecialSymbolToken) \
	SYMBOL(AdditionOperatorSymbol, "+",1,AdditionOperatorToken) \
	SYMBOL(SubtractionOperatorSymbol, "-",1,SubtractionOperatorToken) \
	SYMBOL(MultiplicationOperatorSymbol, "*",1,MultiplicationOperatorToken) \
	SYMBOL(DivisionOperatorSymbol, "/",1,DivisionOperatorToken) \
	SYMBOL(RemainderOperatorSymbol, "%",1,RemainderOperatorToken) \
	SYMBOL(OpenedBracketSymbol, "([",1,OpenedBracketToken) \
	SYMBOL(ClosedBracketSymbol, ")]",1,ClosedBracketToken) \
	SYMBOL(SeparatorSymbol, " \t\n\r",100,SpecialSymbolToken) 

/// <summary>
/// Represents the different types of Symbols used to create a Token
/// </summary>
typedef enum
{
#define SYMBOL(SymbolName,SymbolCharacters,SymbolBlockMax,tokenType) SymbolName,
	SymbolsList
#undef SYMBOL
	SymbolsCount
} Symbol;


const TokenType SymbolTokenTable[SymbolsCount];
const char* SymbolNameTable[SymbolsCount];

//Used to initialize Symbols table
const char* Symbols[SymbolsCount];
Symbol SymbolsTable[SYMBOL_TABLE_SIZE];
void InitSymbolsTable();

/// <summary>
/// Converts the given character to a corresponding Symbol.
/// </summary>
/// <param name="Character">The character to convert to a Symbol.</param>
/// <returns>Returns the corresponding Symbol for the given character.</returns>
Symbol GetSymbol(char Character);