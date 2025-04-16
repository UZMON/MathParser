#include "NumberTokenProcessor.h"
#include "../Constants.h"
#include "../Utils/ErrorPrinter.h"

NumberTokenResult ProcessNumberToken(const SymbolBlock* symbolBlocks , size_t symbolBlocksCount , size_t startIndex)
{
	// Get pointer to the first character of the first symbol block.
	char* firstSymbolBlockPtr = symbolBlocks[startIndex].valuePtr;

	// Initialize the token with default values (assuming it's an integer by default).
	Token currentToken = { 
		.tokenType = IntegerToken,
		.valuePtr = firstSymbolBlockPtr, 
		.length = 0
	};
	
	// Iterate through symbol blocks to determine the full extent of the number token.
	// - If a dot is encountered, the token is upgraded to a DecimalToken.
	// - Only one dot is allowed (e.g., "12.34" is valid, "12.3.4" is not).
	// - The loop ends when a non-digit and non-dot symbol is encountered.
	int dotAdded = 0;
	size_t i = startIndex;
	for (; i < symbolBlocksCount; i++)
	{
		SymbolBlock currentSymbolBlock = symbolBlocks[i];
		Symbol currentSymbol = currentSymbolBlock.symbol;
		if (currentSymbol == DotSymbol)
		{
			// If we've already seen a dot, this is a malformed number.
			if (dotAdded)
			{
				Token errorToken = { ErrorToken,NULL,0 };
				NumberTokenResult errorResult = { errorToken, 0 };
				// @ERROR[NumberTokenProcessor]: Unexpected token / malformed number .
				PrintErrorf("Unexpected token '%c' ", *currentSymbolBlock.valuePtr);
				return errorResult;
			}
			currentToken.tokenType = DecimalToken;
			dotAdded = 1;
		}
		else if (currentSymbol != DigitSymbol)
		{
			// Non-digit and non-dot symbol encountered — end of number.
			break;
		}
		currentToken.length += currentSymbolBlock.length;
	}

	NumberTokenResult result = {
				.token = currentToken ,
				.endPosition = i - 1
	};
	return result;
}