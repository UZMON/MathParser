#include "Token.h"
#include <string.h>

const TokenTypeCategory tokenTypeCategoryTable[TokenType_Count] = {
#define TOKEN(TokenTypeName, NodeType, TokenType_Category) \
    [TokenTypeName##Token] = TokenType_Category,
    TokensList
#undef TOKEN
    /*Expands to :
            [IntegerToken] = ValueTokenCategory ,
            [DecimalToken] = ValueTokenCategory,
            ...etc
    */
};

const ASTNodeType tokenType_NodeType_Table[TokenType_Count] = {
#define TOKEN(TokenTypeName, NodeType, TokenType_Category) \
    [TokenTypeName##Token] = NodeType,
    TokensList
#undef TOKEN
};

const TokenTypeCategory GetTokenCategory(TokenType tokenType)
{
    return tokenTypeCategoryTable[tokenType];
}

ASTNodeType GetTokenNodeType(TokenType tokenType)
{
    return tokenType_NodeType_Table[tokenType];
}

Token CreateToken(TokenType type, const char* valuePtr, size_t length, Position position)
{
    Token token = {
        .tokenType = type,
        .valuePtr = valuePtr,
        .length = length,
        .position = position
    };
    return token;
}