#pragma once
#include "SymbolBlock.h"
#include "../LexerParserShared/Position.h"

// SymbolHandler is a function that creates a token using custom logic for the specific symbol type.
// Takes a SymbolBlockArr and a Position pointer to track the current parsing location.
// Outputs tokens to outTokens, updates outCount, and sets error flag.
// Returns 0 for success , or 1 for error.
typedef int (*SymbolHandler)(
    SymbolBlockArr symbolBlockArr,
    size_t *currentIndex,
    Position *position,
    Token *outTokens,
    size_t *outCount);

// Maps symbols (whose token type is 'SpecialToken') to their corresponding handler functions.
// Unused or irrelevant entries can be NULL.
extern const SymbolHandler symbolHandlerTable[SymbolsCount];
const SymbolHandler GetSymbolHandler(Symbol symbol);

void HandleSimpleTokens(TokenType tokenType, SymbolBlock symbolBlock, Position *position, Token *outTokens, size_t *outCount);

// SymbolHandlers

static int HandleUnknownSymbol(SymbolBlockArr symbolBlockArr, size_t *currentIndex, Position *position, Token *outTokens, size_t *outCount);
static int HandleNumberToken(SymbolBlockArr symbolBlockArr, size_t *currentIndex, Position *position, Token *outTokens, size_t *outCount);
static int HandleSeparator(SymbolBlockArr symbolBlockArr, size_t *currentIndex, Position *position, Token *outTokens, size_t *outCount);
static int HandleNewLine(SymbolBlockArr symbolBlockArr, size_t *currentIndex, Position *position, Token *outTokens, size_t *outCount);