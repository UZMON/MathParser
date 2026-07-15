#include "NumberTokenProcessor.h"
#include "../Constants.h"
#include "../Utils/ErrorPrinter.h"

NumberTokenResult ProcessNumberToken(const SymbolBlock* symbolBlocks, size_t symbolBlocksCount, size_t startIndex, Position position)
{
    const char* firstSymbolBlockPtr = symbolBlocks[startIndex].valuePtr;
    Token currentToken = { .tokenType = IntegerToken, .valuePtr = firstSymbolBlockPtr, .length = 0, .position = position };
    int dotAdded = 0;
    int digitAdded = 0;
    size_t i = startIndex;

    for (; i < symbolBlocksCount; i++) {
        SymbolBlock currentSymbolBlock = symbolBlocks[i];
        Symbol currentSymbol = currentSymbolBlock.symbol;
        if (currentSymbol == DotSymbol) { //  If a dot is encountered, the token is upgraded to a DecimalToken.
            if (dotAdded) { // If we've already seen a dot, this is a malformed number.
                PrintErrorf("Unexpected token '%c' at line %zu, column %zu", *currentSymbolBlock.valuePtr, position.line, position.column + currentToken.length); // @Error[NumberTokenProcessor].
                Token errorToken = { ErrorToken, NULL, 0 };
                NumberTokenResult errorResult = { errorToken, 0 };
                return errorResult;
            }
            currentToken.tokenType = DecimalToken;
            dotAdded = 1;
        } else if (currentSymbol != DigitSymbol) {
            break; // Non-digit and non-dot symbol encountered, end of number.
        } else {
            digitAdded = 1;
        }
        currentToken.length += currentSymbolBlock.length;
    }

    if (!digitAdded) { // A number must contain at least one digit (e.g. a lone "." is not valid).
        PrintErrorf("Malformed number '%.*s' at line %zu, column %zu", (int)currentToken.length, firstSymbolBlockPtr, position.line, position.column); // @Error[NumberTokenProcessor].
        Token errorToken = { ErrorToken, NULL, 0 };
        NumberTokenResult errorResult = { errorToken, 0 };
        return errorResult;
    }

    NumberTokenResult result = { .token = currentToken, .endPosition = i - 1};
    return result;
}