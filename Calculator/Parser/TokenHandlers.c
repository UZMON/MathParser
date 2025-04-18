#include "TokenHandlers.h"

const TokenHandler tokenHandlerTable[] = {
    [ValueTokenCategory] = HandleValue, // e.g., Integer, Decimal
    [BracketTokenCategory] = HandleBracket // (, ), [, ]
};

const TokenHandler GetTokenHandler(TokenTypeCategory category)
{
    return tokenHandlerTable[category];
}

int HandleValue(ASTPool* AST_Pool, ASTNodeStack* AST_Stack, TokenArray tokenArr, size_t* currentIndex, int* expressionDepth)
{
    Token token = tokenArr.tokens[*currentIndex];
    ASTNodeType nodeType = GetTokenNodeType(token.tokenType);
    ASTNode* valueNode = CreateValueNode(AST_Pool, nodeType, token.valuePtr, token.length, token.position, *expressionDepth);
    PushASTNode(AST_Stack, valueNode);
    ReduceTheStack(AST_Stack);
    return 0;
}

int HandleBracket(ASTPool* AST_Pool, ASTNodeStack* AST_Stack, TokenArray tokenArr, size_t* currentIndex, int* expressionDepth)
{
    Token token = tokenArr.tokens[*currentIndex];
    if (token.tokenType == OpenedBracketToken) {
        (*expressionDepth)++;
    } else if (token.tokenType == ClosedBracketToken) {
        (*expressionDepth)--;
    }

    if (*expressionDepth < 0) {
        PrintErrorf("Mismatched parentheses: expected depth higher than 0 but got %d", *expressionDepth); //@Error[Parser].
        return 1;
    }
    return 0;
}