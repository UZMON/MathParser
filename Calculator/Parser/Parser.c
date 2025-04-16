#pragma once
#include "Parser.h"
#include "../Utils/ErrorPrinter.h"

const TokenHandler tokenHandlerTable[] = {
	[ValueTokenCategory] = HandleValue,   // e.g., Integer, Decimal
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
	ASTNode* valueNode = CreateValueNode(AST_Pool, nodeType, token.valuePtr, token.length);

	ASTNode* leftNode = PeekASTNode(AST_Stack);
	// If there is no left node in the current stack, push the value node.
	if (!leftNode)
	{
		PushASTNode(AST_Stack, valueNode);
		return 0;
	}

	NodeCategory leftNodeCategory = NodeTypeCategoryTable[leftNode->nodeType];
	// If the left node is not an operator, this is invalid grammar.
	if (leftNodeCategory != OperatorNodeCategory)
	{
		// @ERROR[Parser]: Unexpected value token after non-operator node.
		PrintErrorf("Unexpected token at '%.*s'", (int)token.length, token.valuePtr);
		return 1;
	}

	// If the left node is an operator, attach valueNode as its right child.
	leftNode->op.right = valueNode;
	return 0;
}

int HandleOp(ASTPool* AST_Pool, ASTNodeStack* AST_Stack, Token token)
{
	ASTNodeType nodeType = TokenType_NodeType_Table[token.tokenType];
	ASTNode* leftNode = PeekASTNode(AST_Stack);
	if (!leftNode)
	{
		// @Error[Parser]: Expected a left value for the operator.
		PrintErrorf("Expected a left value for the operator at '%.*s'", (int)token.length, token.valuePtr);
		return 1;
	}

	//TODO ADD Precedence 
	//TODO Check if operator precedence less or more ...
	//TODO Add leftside and rightside Category array for what operator accepts , this helps for checking unexpected tokens/nodes

	ASTNode* operatorNode = CreateOperatorNode(AST_Pool, nodeType, leftNode, NULL);
	PushASTNode(AST_Stack, operatorNode);
	return 0;
}

int HandleBracket(ASTPool* AST_Pool, ASTNodeStack* AST_Stack, Token token)
{

}
