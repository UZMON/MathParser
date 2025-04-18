#include "Lexer.h"

#include <stdlib.h>
#include <string.h>

#include "../Constants.h"
#include "../Utils/ErrorPrinter.h"
#include "../Utils/Macros.h"
#include "SymbolBlock.h"
#include "SymbolHandlers.h"

void InitLexer() { InitSymbolsTable(); }

void Lex(char* dataPtr, Token* outTokens, size_t* outCount, int* error)
{
    *error = 0;

    SymbolBlock SymbolBlocks[MAX_EXPRESSION_SIZE];
    size_t symbolBlocksCount = 0;
    ReadAllSymbolBlocks(dataPtr, SymbolBlocks, &symbolBlocksCount);

    Token tokens[MAX_EXPRESSION_SIZE] = { 0 };
    SymbolBlockArr symbolBlockArr = { SymbolBlocks, symbolBlocksCount };
    ReadTokens(symbolBlockArr, outTokens, outCount, error);
}

int ReadTokens(SymbolBlockArr symbolBlockArr, Token* outTokens, size_t* outCount)
{
    *outCount = 0;
    Position position = { 1, 1 }; // Line : 1 , Column : 1
    SymbolBlock* symbolBlocks = symbolBlockArr.symbolBlocks;
    size_t symbolBlocksCount = symbolBlockArr.length;

    for (size_t i = 0; i < symbolBlocksCount; i++) {
        SymbolBlock currentSymbolBlock = symbolBlocks[i];
        Symbol currentSymbol = currentSymbolBlock.symbol;
        TokenType mappedTokenType = GetSymbolTokenType(currentSymbol);

        // Handle special symbols with custom token logic
        if (mappedTokenType == SpecialToken) {
            SymbolHandler handler = GetSymbolHandler(currentSymbol);
            if (!handler) {
                PrintErrorf("Can't find suitable Token for %s", GetSymbolName(currentSymbol)); // @Error[Lexer].
                return 1;
            }
            if (handler(symbolBlockArr, &i, &position, outTokens, outCount)) // Run Symbol Handler
                return 1; // error
            continue;
        }
        HandleSimpleTokens(mappedTokenType, currentSymbolBlock, position, outTokens, outCount); // e.g. operators, parentheses, etc.
    }
    return 0;
}