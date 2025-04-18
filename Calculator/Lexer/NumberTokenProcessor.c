#include "NumberTokenProcessor.h"
#include "../Constants.h"
#include "../Utils/ErrorPrinter.h"

NumberTokenResult ProcessNumberToken(const SymbolBlock* symbolBlocks, size_t symbolBlocksCount, size_t startIndex)
{
    char* firstSymbolBlockPtr = symbolBlocks[startIndex].valuePtr;
    Token currentToken = { .tokenType = IntegerToken, .valuePtr = firstSymbolBlockPtr, .length = 0 };
    int dotAdded = 0;
    size_t i = startIndex;

    for (; i < symbolBlocksCount; i++) { 
        SymbolBlock currentSymbolBlock = symbolBlocks[i];
        Symbol currentSymbol = currentSymbolBlock.symbol;
        if (currentSymbol == DotSymbol) { //  If a dot is encountered, the token is upgraded to a DecimalToken.
            if (dotAdded) { // If we've already seen a dot, this is a malformed number.
                PrintErrorf("Unexpected token '%c' ", *currentSymbolBlock.valuePtr); // @Error[NumberTokenProcessor].
                Token errorToken = { ErrorToken, NULL, 0 };
                NumberTokenResult errorResult = { errorToken, 0 };
                return errorResult;
            }
            currentToken.tokenType = DecimalToken;
            dotAdded = 1;
        } else if (currentSymbol != DigitSymbol) {
            break; // Non-digit and non-dot symbol encountered — end of number.
        }
        currentToken.length += currentSymbolBlock.length;
    }
    NumberTokenResult result = { .token = currentToken, .endPosition = i - 1};
    return result;
}