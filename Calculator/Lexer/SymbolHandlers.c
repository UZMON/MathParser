#include "SymbolHandlers.h"
#include "NumberTokenProcessor.h"

const SymbolHandler symbolHandlerTable[] = {
	[DigitSymbol] = HandleNumberToken,
	[DotSymbol] = HandleNumberToken,
	[UnknownSymbol] = HandleUnknownSymbol,
	[SeparatorSymbol] = HandleSeparator,
	[NewLineSymbol] = HandleNewLine,
};

static void HandleNumberToken(SymbolBlockArr symbolBlockArr, size_t* currentIndex, Position* position, Token* outTokens, size_t* outCount, int* error)
{
	SymbolBlock* symbolBlocks = symbolBlockArr.symbolBlocks;
	size_t symbolBlocksCount = symbolBlockArr.length;
	NumberTokenResult result = ProcessNumberToken(symbolBlocks, symbolBlocksCount, *currentIndex);
	outTokens[(*outCount)++] = result.token;
	position->column += result.token.length;
	*currentIndex = result.endPosition;
}

static void HandleUnknownSymbol(SymbolBlockArr symbolBlockArr, size_t* currentIndex, Position* position, Token* outTokens, size_t* outCount, int* error)
{
	SymbolBlock currentSymbolBlock = symbolBlockArr.symbolBlocks[*currentIndex];
	// @ERROR[Lexer]: Unknown Symbol found
	PrintErrorf("Unknown Symbol found: '%c'", currentSymbolBlock.valuePtr);
	*error = 1;
}

static void HandleSeparator(SymbolBlockArr symbolBlockArr, size_t* currentIndex, Position* position, Token* outTokens, size_t* outCount, int* error)
{
	SymbolBlock currentSymbolBlock = symbolBlockArr.symbolBlocks[*currentIndex];
	position->column += currentSymbolBlock.length;
}

static void HandleNewLine(SymbolBlockArr symbolBlockArr, size_t* currentIndex, Position* position, Token* outTokens, size_t* outCount, int* error)
{
	position->line++;
	position->column = 1;
}