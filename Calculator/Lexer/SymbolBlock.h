#pragma once
#include "../LexerParserShared/Token.h"
#include "Symbol.h"

/// <summary>
/// The SymbolBlock is an array of identical Symbol types found next to each other (The maximum length depends on the symbol type).
/// </summary>
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
const size_t SymbolBlockMaximumLength[SymbolsCount];

/// <summary>
///  Reads a block of consecutive characters from `dataptr` that all map to the same `wantedSymbol`.
/// </summary>
/// <param name="dataPtr">The pointer to the first character of the SymbolBlock.</param>
/// <param name="wantedSymbol">The type of symbol for the SymbolBlock to be read.</param>
/// <returns>Returns the resulting SymbolBlock.</returns>
SymbolBlock ReadSymbolBlock(char* dataPtr, Symbol wantedSymbol);

/// <summary>
/// Reads all SymbolBlocks found in the input string.
/// </summary>
/// <param name="dataPtr">Pointer to the null-terminated input string.</param>
/// <param name="outSymbolBlocks">SymbolBlock array (of size MAX_EXPRESSION_SIZE ) ; parsed blocks are copied to this array.</param>
/// <param name="outCount">Pointer to the count of symbolblocks found.</param>
void ReadSymbolBlocks ( const char* dataPtr , SymbolBlock* outSymbolBlocks , size_t* outCount );