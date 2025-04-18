#pragma once
#include <stddef.h>
#include "../LexerParserShared/Token.h"
#include "../Constants.h"
#include "ASTNode.h"
#include "ASTNodeStack.h"
#include "ASTPool.h"

/// <summary>
/// Parses the given tokens into an Abstract Syntax Tree (AST) stack. 
/// The resulting stack should contain a single AST node (the root) at the end.
/// </summary>
/// <param name="tokenArr">The array of tokens to parse.</param>
/// <param name="StartIndex">index to start parsing from within the token array.</param>
/// <param name="AST_Pool">Pointer to the AST pool where nodes will be allocated.</param>
/// <param name="out_AST_Stack">Outputs the AST stack containing the root node.</param>
/// <returns>Returns 0 on success, or 1 if an error occurs.</returns>
int ParseTokensToStack (TokenArray tokenArr , ASTPool* AST_Pool , ASTNodeStack* out_AST_Stack );
