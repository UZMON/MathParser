#pragma once
#include "../LexerParserShared/Token.h"
#include "Symbol.h"

// The SymbolBlock is an array of identical Symbol types found next to each other (The maximum length depends on the symbol type).
typedef struct SymbolBlock SymbolBlock;
struct SymbolBlock
{
	Symbol symbol;
	const char* valuePtr;
	size_t length;
};

typedef struct SymbolBlockArr SymbolBlockArr;
struct SymbolBlockArr
{
	SymbolBlock* symbolBlocks;
	size_t length;
};

/// <summary>
/// Reads all SymbolBlocks found in the input string.
/// </summary>
/// <param name="dataPtr">Pointer to the null-terminated input string.</param>
/// <param name="length">The length of the string pointed to by dataPtr (i.e. strlen(dataPtr)).</param>
/// <param name="outSymbolBlocks">SymbolBlock array ; parsed blocks are copied to this array.</param>
/// <param name="capacity">The number of elements outSymbolBlocks can hold.</param>
/// <param name="outCount">Pointer to the count of symbolblocks found.</param>
/// <returns>0 on success, or 1 if dataPtr produced more symbol blocks than capacity allows.</returns>
int ReadAllSymbolBlocks ( const char* dataPtr , size_t length , SymbolBlock* outSymbolBlocks , size_t capacity , size_t* outCount );