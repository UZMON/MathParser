#include <stdlib.h>
#include <string.h>
#include "Lexer.h"
#include "../Utils/ErrorPrinter.h"
#include "SymbolBlock.h"
#include "NumberTokenProcessor.h"
#include "../Constants.h"

void Lex(char* dataPtr, Token* outTokens, size_t* outCount, int* error)
{
	*error = 0;
	SymbolBlock SymbolBlocks[MAX_EXPRESSION_SIZE];
	size_t symbolBlocksCount = 0;
	ReadSymbolBlocks(dataPtr,SymbolBlocks,&symbolBlocksCount);
	Token tokens[MAX_EXPRESSION_SIZE];
	size_t tokensCount = 0;
	ReadTokens(SymbolBlocks,symbolBlocksCount,outTokens,&tokensCount,error);
	*outCount = tokensCount;
}

void ReadSymbolBlocks(const char* dataPtr, SymbolBlock* outSymbolBlocks, size_t* outCount)
{
	size_t length = strlen(dataPtr);
	size_t symbolBlocksCount = 0;
	for (size_t i = 0; i < length;)
	{
		char currentCharacter = dataPtr[i];
		Symbol currentSymbol = GetSymbol(currentCharacter);
		SymbolBlock currentToken = ReadSymbolBlock(dataPtr + i, currentSymbol);
		outSymbolBlocks[symbolBlocksCount] = currentToken;
		symbolBlocksCount++;
		i += currentToken.length;
	}
	*outCount = symbolBlocksCount;
}

void ReadTokens(const SymbolBlock* symbolBlocks, size_t symbolBlocksCount, Token* outTokens, size_t* outCount, int* error)
{
	*error = 0;
	size_t tokensCount = 0;
	for (size_t i = 0; i < symbolBlocksCount; i++)
	{
		SymbolBlock currentSymbolBlock = symbolBlocks[i];
		Symbol currentSymbol = currentSymbolBlock.symbol;
		// Handle numeric tokens (digits or leading dot)
		if (currentSymbol == DigitSymbol || currentSymbol == DotSymbol)
		{
			NumberTokenResult result = ProcessNumberToken(symbolBlocks, symbolBlocksCount, i);
			outTokens[tokensCount++] = result.token;
			i = result.endPosition;
			continue;
		}

		// Handle unknown symbols
		if (currentSymbol == UnknownSymbol)
		{
			PrintErrorf("Unknown Symbol found: '%c'", *currentSymbolBlock.valuePtr);
			*error = 1;
			return;
		}

		// Skip separator (used to mark end of input or expression)
		if (currentSymbol == SeparatorSymbol)
		{
			continue;
		}

		// Handle unmapped symbols
		TokenType mappedTokenType = SymbolTokenTable[currentSymbol];
		if (mappedTokenType == ErrorToken)
		{
			PrintErrorf("Can't find suitable Token for %s", SymbolNameTable[currentSymbol]);
			*error = 1;
			return;
		}

		// Handle all other valid symbols (operators, parentheses, etc.)
		Token token = {
			.tokenType = mappedTokenType,
			.valuePtr = currentSymbolBlock.valuePtr,
			.length = currentSymbolBlock.length
		};

		outTokens[tokensCount++] = token;
	}
	*outCount = tokensCount;
}
