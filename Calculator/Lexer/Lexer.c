#include <stdlib.h>
#include <string.h>
#include "Lexer.h"
#include "SymbolHandlers.h"
#include "../Utils/ErrorPrinter.h"
#include "SymbolBlock.h"
#include "../Constants.h"

void Lex(char* dataPtr, Token* outTokens, size_t* outCount, int* error)
{
	*error = 0;

	SymbolBlock SymbolBlocks[MAX_EXPRESSION_SIZE];
	size_t symbolBlocksCount = 0;
	ReadSymbolBlocks(dataPtr , SymbolBlocks , &symbolBlocksCount);

	Token tokens[MAX_EXPRESSION_SIZE] = {0};
	SymbolBlockArr symbolBlockArr = { SymbolBlocks , symbolBlocksCount };
	ReadTokens(symbolBlockArr , outTokens , outCount , error);
}

void ReadTokens(SymbolBlockArr symbolBlockArr, Token* outTokens, size_t* outCount, int* error)
{
	*error = 0;
	*outCount = 0;
	Position position = { 1 , 1 }; // Line : 1 , Column : 1 
	SymbolBlock* symbolBlocks = symbolBlockArr.symbolBlocks;
	size_t symbolBlocksCount = symbolBlockArr.length;
	
	for (size_t i = 0; i < symbolBlocksCount; i++)
	{
		SymbolBlock currentSymbolBlock = symbolBlocks[i];
		Symbol currentSymbol = currentSymbolBlock.symbol;
		TokenType mappedTokenType = SymbolTokenTable[currentSymbol];

		// Handle special symbols with custom token logic
		if (mappedTokenType == SpecialToken)
		{
			SymbolHandler symbolHandler = symbolHandlerTable[currentSymbol];
			
			if(!symbolHandler)
			{
				// @ERROR[Lexer]: No suitable Token for symbol
				PrintErrorf("Can't find suitable Token for %s", SymbolNameTable[currentSymbol]);
				*error = 1;
				return;
			}

			symbolHandler(symbolBlockArr, &i, &position, outTokens, outCount, error);
			if (*error) return;
			continue;
		}

		// Handle all simple symbols (operators, identifiers, parentheses, etc.)
		Token token = CreateToken(mappedTokenType, currentSymbolBlock.valuePtr, currentSymbolBlock.length, position);
		position.column += currentSymbolBlock.length;
		outTokens[(*outCount)++] = token;
	}
}