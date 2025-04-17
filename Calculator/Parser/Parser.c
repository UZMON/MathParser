#pragma once
#include "Parser.h"
#include "../Utils/ErrorPrinter.h"
#include "../Utils/Macros.h"

const TokenHandler tokenHandlerTable[] = {
	[ValueTokenCategory] = HandleOp,   // e.g., Integer, Decimal
	[OperatorTokenCategory] = HandleOp,      // +, -, *, etc...
	[BracketTokenCategory] = HandleBracket  // (, ), [, ]
};

void ParseTokensToStack(TokenArray tokenArr , size_t StartIndex , ASTPool* AST_Pool, ASTNodeStack* out_AST_Stack )
{

	for (size_t i = StartIndex; i < tokenArr.length; i++)
	{
		Token currentToken = tokenArr.tokens[i];
		TokenTypeCategory currentTokenCategory = TokenTypeCategoryTable[currentToken.tokenType];
		//Runs the handler according to the token category.
		//This modifies the AST_Pool and AST_Stack.
		int error = tokenHandlerTable[currentTokenCategory](&AST_Pool, &out_AST_Stack, currentToken);
		if (error)
		{
			//TODO...
		}
	} 
}

int HandleValue(ASTPool* AST_Pool, ASTNodeStack* AST_Stack, Token token)
{
	ASTNodeType nodeType = TokenType_NodeType_Table[token.tokenType];
	ASTNode* valueNode = CreateValueNode(AST_Pool, nodeType, token.valuePtr, token.length, token.position);
	PushASTNode(AST_Stack, valueNode);
	return 0;
}

int HandleOp(ASTPool* AST_Pool, ASTNodeStack* AST_Stack, Token token)
{
	ASTNodeType nodeType = TokenType_NodeType_Table[token.tokenType];
	ASTNode* leftNode = PeekASTStack(AST_Stack);
	if (!leftNode)
	{
		// @Error[Parser]: Expected a left value for the operator.
		PrintErrorf("Expected a left value for the operator '%.*s' at ( %d, %d )", (int)token.length, token.valuePtr , token.position.line , token.position.column);
		return 1;
	}

	int currentPrecedence = NodeTypePrecedenceTable[nodeType];
	int leftSidePrecedence = NodeTypePrecedenceTable[leftNode->nodeType];

	if (currentPrecedence > leftSidePrecedence)
	{
		//Pop left node.
		leftNode = PopASTStack(AST_Stack);
		ASTNode* currentNode = CreateOperatorNode(AST_Pool, nodeType, leftNode, NULL);
		PushASTNode(AST_Stack, currentNode);
		return 0;
	}
	// If

	
	//TODO Add leftside and rightside Category array for what operator accepts , this helps for checking unexpected tokens/nodes
	return 0;
}

int HandleBracket(ASTPool* AST_Pool, ASTNodeStack* AST_Stack, Token token)
{

}

//TODO : Move the Note to somewhere more suitable.
// Note : 
//			- It is obligatory by this logic that any node ( other than the top node !! ) closer to the topNode will always have higher priority than the ones far away