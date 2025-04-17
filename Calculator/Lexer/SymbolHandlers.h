#pragma once
#include "SymbolBlock.h"
#include "../LexerParserShared/Position.h"

// SymbolHandler is a function that creates a token using custom logic for the specific symbol type.
// Takes a SymbolBlockArr and a Position pointer to track the current parsing location.
// Outputs tokens to outTokens, updates outCount, and sets error flag.
// Returns void — use the error output parameter to signal failure.
typedef void (*SymbolHandler)(
    SymbolBlockArr symbolBlockArr ,
    size_t* currentIndex ,
    Position* position ,
    Token* outTokens ,
    size_t* outCount ,
    int* error
);

// Maps symbols (whose token type is 'SpecialToken') to their corresponding handler functions.
// Unused or irrelevant entries can be NULL.
const SymbolHandler symbolHandlerTable[ SymbolsCount ];

void HandleUnknownSymbol ( SymbolBlockArr , size_t* , Position* , Token* , size_t* , int* );
void HandleNumberToken ( SymbolBlockArr , size_t* , Position* , Token* , size_t* , int* );
void HandleSeparator ( SymbolBlockArr , size_t* , Position* , Token* , size_t* , int* );
void HandleNewLine ( SymbolBlockArr , size_t* , Position* , Token* , size_t* , int* );