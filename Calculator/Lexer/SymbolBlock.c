#include <string.h>
#include <math.h>
#include "SymbolBlock.h"

const size_t SymbolBlockMaximumLength[SymbolsCount] = {
	#define SYMBOL(SymbolName,SymbolCharacters,SymbolBlockMax,tokenType)  \
		[SymbolName] = SymbolBlockMax, 
		SymbolsList
	#undef SYMBOL
		/*Expands to :
			[UnknownSymbol] = 1,
			[NumberSymbol] = 100,
			...etc
		*/
};

SymbolBlock ReadSymbolBlock(char* dataPtr, Symbol wantedSymbol)
{
	size_t length = strlen(dataPtr);
	size_t CurrentSymbolBlockMaxLength = SymbolBlockMaximumLength[wantedSymbol];
	SymbolBlock CurrentSymbolBlock = { wantedSymbol, dataPtr, 0 };
	// A SymbolBlock is created by incrementing its length for every matching character.
	for (int i = 0; i < length; i++)
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