#pragma once
#include "Parser.h"
#include "../Utils/ErrorPrinter.h"
#include "../Utils/Macros.h"
#include "TokenHandlers.h"

int ParseTokensToStack(TokenArray tokenArr, ASTPool* AST_Pool, ASTNodeStack* out_AST_Stack)
{
    int expressionDepth = 0;
    for (size_t i = 0; i < tokenArr.length; i++) {
        Token currentToken = tokenArr.tokens[i];
        TokenTypeCategory currentTokenCategory = GetTokenCategory(currentToken.tokenType);
        TokenHandler handler = GetTokenHandler(currentTokenCategory); // Find the handler according to the token category.
        if (Exists(handler)) {
            int error = handler(AST_Pool, out_AST_Stack, tokenArr, &i, &expressionDepth);
            if (error)
                return 1;
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