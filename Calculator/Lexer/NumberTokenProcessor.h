#pragma once
#include "Lexer.h"

/// <summary>
/// Represents the result of processing a number token from a sequence of SymbolBlocks.
/// Includes the parsed token and the index of the last SymbolBlock that forms part of the token.
/// </summary>
typedef struct NumberTokenResult NumberTokenResult;
struct NumberTokenResult
{
	/// The resulting number token (IntegerToken or DecimalToken).
	Token token;
	/// The index of the last SymbolBlock included in the token.
	size_t endPosition;
};

/// <summary>
/// Creates a number token based on a sequence of SymbolBlocks.
/// For example: DigitSymbolBlock, DotSymbol, DigitSymbolBlock => DecimalToken.
/// </summary>
/// <param name="symbolBlocks">The array of SymbolBlocks to process.</param>
/// <param name="symbolBlocksCount">The count of SymbolBlocks inside the symbolBlocks array.</param>
/// <param name="startIndex">The starting index in the SymbolBlock array.</param>
/// <param name="position">The position of the start of the number token, used for error reporting.</param>
/// <returns>
/// A NumberTokenResult containing the parsed token and the ending index.
/// If the token is invalid, the token field will be an ErrorToken (e.g., token.valuePtr = NULL).
/// </returns>
NumberTokenResult ProcessNumberToken(const SymbolBlock* symbolBlocks, size_t symbolBlocksCount, size_t startIndex, Position position );