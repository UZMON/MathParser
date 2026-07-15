#include "SymbolHandlers.h"
#include "NumberTokenProcessor.h"
#include "../Utils/ErrorPrinter.h"

const SymbolHandler symbolHandlerTable[] = {
    [DigitSymbol] = HandleNumberToken,
    [DotSymbol] = HandleNumberToken,
    [UnknownSymbol] = HandleUnknownSymbol,
    [SeparatorSymbol] = HandleSeparator,
    [NewLineSymbol] = HandleNewLine,
};

const SymbolHandler GetSymbolHandler(Symbol symbol)
{
        return symbolHandlerTable[symbol];
}

void HandleSimpleTokens(TokenType tokenType, SymbolBlock symbolBlock, Position *position, Token *outTokens, size_t *outCount)
{
        Token token = CreateToken(tokenType, symbolBlock.valuePtr, symbolBlock.length, *position);
        position->column += symbolBlock.length;
        outTokens[(*outCount)++] = token;
}

static int HandleNumberToken(SymbolBlockArr symbolBlockArr, size_t *currentIndex, Position *position, Token *outTokens, size_t *outCount)
{
        SymbolBlock *symbolBlocks = symbolBlockArr.symbolBlocks;
        size_t symbolBlocksCount = symbolBlockArr.length;
        NumberTokenResult result = ProcessNumberToken(symbolBlocks, symbolBlocksCount, *currentIndex, *position);
        if (result.token.tokenType == ErrorToken)
        {
                return 1;
        }
        outTokens[(*outCount)++] = result.token;
        position->column += result.token.length;
        *currentIndex = result.endPosition;
        return 0;
}

static int HandleUnknownSymbol(SymbolBlockArr symbolBlockArr, size_t *currentIndex, Position *position, Token *outTokens, size_t *outCount)
{
        SymbolBlock currentSymbolBlock = symbolBlockArr.symbolBlocks[*currentIndex];
        PrintErrorf("Unknown Symbol found: '%c' at line %zu, column %zu", *currentSymbolBlock.valuePtr, position->line, position->column); // @Error[Lexer].
        return 1;
}

static int HandleSeparator(SymbolBlockArr symbolBlockArr, size_t *currentIndex, Position *position, Token *outTokens, size_t *outCount)
{
        SymbolBlock currentSymbolBlock = symbolBlockArr.symbolBlocks[*currentIndex];
        position->column += currentSymbolBlock.length;
        return 0;
}

static int HandleNewLine(SymbolBlockArr symbolBlockArr, size_t *currentIndex, Position *position, Token *outTokens, size_t *outCount)
{
        position->line++;
        position->column = 1;
        return 0;
}