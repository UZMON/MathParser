#pragma once
#include "../LexerParserShared/Token.h"
#include "Symbol.h"

// The SymbolBlock is an array of identical Symbol types found next to each other (The maximum length depends on the symbol type).
typedef struct SymbolBlock SymbolBlock;
struct SymbolBlock
{
	Symbol symbol;
	char* valuePtr;
	size_t length;
};

typedef struct SymbolBlockArr SymbolBlockArr;
struct SymbolBlockArr
{
	SymbolBlock* symbolBlocks;
	size_t length;
};

//The maximum length of SymbolBlock depending on the symbol type.
const size_t symbolBlockMaximumLengthTable[SymbolsCount];
const size_t GetSymbolMaximumLength ( Symbol symbol );

//  Reads a block of consecutive characters from `dataptr` that all map to the same `wantedSymbol`.
SymbolBlock ReadSymbolBlock(char* dataPtr, Symbol wantedSymbol);

/// <summary>
/// Reads all SymbolBlocks found in the input string.
/// </summary>
/// <param name="dataPtr">Pointer to the null-terminated input string.</param>
/// <param name="outSymbolBlocks">SymbolBlock array (of size MAX_EXPRESSION_SIZE ) ; parsed blocks are copied to this array.</param>
/// <param name="outCount">Pointer to the count of symbolblocks found.</param>
void ReadAllSymbolBlocks ( const char* dataPtr , SymbolBlock* outSymbolBlocks , size_t* outCount );