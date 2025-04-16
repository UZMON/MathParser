#include <string.h>
#include "Token.h"

const TokenTypeCategory TokenTypeCategoryTable[TokenType_Count] =
{
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

const ASTNodeType TokenType_NodeType_Table[TokenType_Count] =
{
	#define TOKEN(TokenTypeName, NodeType, TokenType_Category) \
		[TokenTypeName##Token] = NodeType,
		TokensList
	#undef TOKEN
};

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