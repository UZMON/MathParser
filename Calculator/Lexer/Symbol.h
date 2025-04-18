#pragma once
#include <stddef.h>
#include "../LexerParserShared/Token.h"

#define DIGITS        "0123456789"
#define WHITESPACE    " \t\r"
#define BRACKETS_OPEN "(["
#define BRACKETS_CLOSE ")]"

#define SYMBOL_TABLE_SIZE 128
// NOTE: You may want to adjust SYMBOL_TABLE_SIZE based on the highest Unicode value
// used in any of the character sets below.
//
// Each SYMBOL is defined using:
// SYMBOL(SymbolName, CharacterSet, MaxLength, TokenType)
// 
// TokenType is set to SpecialToken for those handled specially in ReadTokens() of Lexer.c
// i.e they can't be converted directly into a token.
#define SymbolsList \
    SYMBOL(Unknown,                "",           1,   SpecialToken) /* Triggers error */ \
    SYMBOL(Digit,                  DIGITS, 100, SpecialToken) \
    SYMBOL(Dot,                    ".",          1,   SpecialToken) \
    SYMBOL(AdditionOperator,      "+",          1,   AdditionOperatorToken) \
    SYMBOL(SubtractionOperator,   "-",          1,   SubtractionOperatorToken) \
    SYMBOL(MultiplicationOperator,"*",          1,   MultiplicationOperatorToken) \
    SYMBOL(DivisionOperator,      "/",          1,   DivisionOperatorToken) \
    SYMBOL(RemainderOperator,     "%",          1,   RemainderOperatorToken) \
    SYMBOL(OpenedBracket,         BRACKETS_OPEN,         1,   OpenedBracketToken) \
    SYMBOL(ClosedBracket,          BRACKETS_CLOSE,         1,   ClosedBracketToken) \
    SYMBOL(Separator,                 WHITESPACE,    100, SpecialToken) \
    SYMBOL(NewLine,                      "\n",    1, SpecialToken) \

// Represents the different types of Symbols used to create a Token
typedef enum Symbol Symbol;
enum Symbol
{
#define SYMBOL(SymbolName,SymbolCharacters,SymbolBlockMax,tokenType) SymbolName##Symbol,
	SymbolsList
#undef SYMBOL
	SymbolsCount //Should Always be the last ! 
};


const TokenType SymbolTokenTable[SymbolsCount];
const TokenType GetSymbolTokenType ( Symbol symbol );

const char* SymbolNameTable[SymbolsCount];
const char* GetSymbolName ( Symbol symbol );

//Used to initialize Symbols table
const char* Symbols[SymbolsCount];
Symbol SymbolsTable[SYMBOL_TABLE_SIZE];
void InitSymbolsTable();
// Converts the given character to a corresponding Symbol.
Symbol GetSymbol(char Character);