#include "Parser.h"
#include "../Utils/ErrorPrinter.h"
#include "../Utils/Macros.h"
#include "TokenHandlers.h"

int ParseTokensToStack(TokenArray tokenArr, ASTPool* AST_Pool, ASTNodeStack* out_AST_Stack)
{
    if (tokenArr.length >= MAX_AST_NODES) {
        PrintErrorf("Too many tokens to parse (max %d)", MAX_AST_NODES - 1); // @Error[Parser].
        return 1;
    }

    int expressionDepth = 0;
    for (size_t i = 0; i < tokenArr.length; i++) {
        Token currentToken = tokenArr.tokens[i];
        TokenTypeCategory currentTokenCategory = GetTokenCategory(currentToken.tokenType);
        if (currentTokenCategory < 0 || currentTokenCategory >= TokenTypeCategory_Count) {
            PrintErrorf("Token type %d cannot be parsed", (int)currentToken.tokenType); // @Error[Parser].
            return 1;
        }

        TokenHandler handler = GetTokenHandler(currentTokenCategory); // Find the handler according to the token category.
        if (Exists(handler)) {
            size_t previousIndex = i;
            int error = handler(AST_Pool, out_AST_Stack, tokenArr, &i, &expressionDepth);
            if (error)
                return 1;
            if (i < previousIndex) {
                PrintErrorf("Internal error: token handler moved index backward"); // @Error[Parser].
                return 1;
            }
            continue;
        }
        // No Handlers for the token , we just push it to the stack.
        ASTNodeType currentNodeType = GetTokenNodeType(currentToken.tokenType);
        int error = EmitNode(AST_Pool, out_AST_Stack, currentNodeType, currentToken.position, expressionDepth);
        if (error)
            return 1;
    }
    // Reduces the stack properly when no more tokens can be found.
    return EmitTerminalNode(AST_Pool, out_AST_Stack, expressionDepth);
}