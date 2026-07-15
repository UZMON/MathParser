#include "SymbolBlock.h"
#include "../Utils/ErrorPrinter.h"
#include <math.h>
#include <string.h>

static const size_t symbolBlockMaximumLengthTable[SymbolsCount] = {
#define SYMBOL(SymbolName, SymbolCharacters, SymbolBlockMax, tokenType) \
        [SymbolName##Symbol] = SymbolBlockMax,
    SymbolsList
#undef SYMBOL
    /*Expands to :
            [UnknownSymbol] = 1,
            [NumberSymbol] = 100,
            ...etc
    */
};

static const size_t GetSymbolMaximumLength(Symbol symbol)
{
        size_t maxLength = symbolBlockMaximumLengthTable[symbol];
        return maxLength > 0 ? maxLength : 1;
}

static SymbolBlock ReadSymbolBlock(const char *dataPtr, Symbol wantedSymbol)
{
        size_t length = strlen(dataPtr);
        size_t CurrentSymbolBlockMaxLength = GetSymbolMaximumLength(wantedSymbol);
        SymbolBlock CurrentSymbolBlock = {wantedSymbol, dataPtr, 0};
        // A SymbolBlock is created by incrementing its length for every matching symbol.
        for (size_t i = 0; i < length; i++)
        {
                char CurrentCharacter = dataPtr[i];
                Symbol CurrentTokenSymbol = GetSymbol(CurrentCharacter);
                // The block ends when:
                //   - A character maps to a different symbol, or
                //   - The block reaches its maximum allowed length (based on wantedSymbol).
                if (CurrentTokenSymbol != wantedSymbol || CurrentSymbolBlock.length == CurrentSymbolBlockMaxLength)
                {
                        break;
                }
                CurrentSymbolBlock.length++;
        }
        return CurrentSymbolBlock;
}

int ReadAllSymbolBlocks(const char *dataPtr, size_t length, SymbolBlock *outSymbolBlocks, size_t capacity, size_t *outCount)
{
        size_t symbolBlocksCount = 0;

        for (size_t i = 0; i < length;)
        {
                if (symbolBlocksCount >= capacity)
                {
                        PrintErrorf("Too many symbol blocks (max %zu)", capacity); // @Error[SymbolBlock].
                        *outCount = symbolBlocksCount;
                        return 1;
                }
                char currentCharacter = dataPtr[i];
                Symbol currentSymbol = GetSymbol(currentCharacter);
                SymbolBlock currentBlock = ReadSymbolBlock(dataPtr + i, currentSymbol);
                outSymbolBlocks[symbolBlocksCount] = currentBlock;
                symbolBlocksCount++;
                i += currentBlock.length;
        }

        *outCount = symbolBlocksCount;
        return 0;
}