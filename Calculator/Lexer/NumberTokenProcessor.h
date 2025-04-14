#pragma once
#include "Lexer.h"

/// <summary>
/// Represents the result of processing a number token from a sequence of SymbolBlocks.
/// </summary>
/// <remarks>
/// Includes the parsed token and the index of the last SymbolBlock that forms part of the token.
/// </remarks>
/// <field name="token">The resulting number token (IntegerToken or DecimalToken).</field>
/// <field name="endPosition">The index of the last SymbolBlock included in the token.</field>
typedef struct
{
	/// The resulting number token (IntegerToken or DecimalToken).
	Token token;
	/// The index of the last SymbolBlock included in the token.
	size_t endPosition;
} NumberTokenResult;

/// <summary>
/// Creates a number token based on a sequence of SymbolBlocks.
/// For example: DigitSymbolBlock, DotSymbol, DigitSymbolBlock => DecimalToken.
/// </summary>
/// <param name="symbolBlocks">The array of SymbolBlocks to process.</param>
/// <param name="symbolBlocksCount">The count of SymbolBlocks inside the symbolBlocks array.</param>
/// <param name="startPosition">The starting index in the SymbolBlock array.</param>
/// <returns>
/// A NumberTokenResult containing the parsed token and the ending index.
/// If the token is invalid, the token field will be an ErrorToken (e.g., token.valuePtr = NULL).
/// </returns>
NumberTokenResult ProcessNumberToken(const SymbolBlock* symbolBlocks, size_t symbolBlocksCount, size_t startPosition);