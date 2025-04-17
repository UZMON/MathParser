#include "Priority.h"

int Priority_MoreThan(ASTNodeType leftValue, ASTNodeType rightValue)
{
	//Lower Precedence => Higher Priority.
	return GetNodePrecedence(leftValue) < GetNodePrecedence(rightValue);
}

int Priority_LessThan(ASTNodeType leftValue, ASTNodeType rightValue)
{
	//Higher Precedence => Lowe Priority.
	return GetNodePrecedence(leftValue) > GetNodePrecedence(rightValue);
}

int Priority_Equal(ASTNodeType leftValue, ASTNodeType rightValue)
{
	return GetNodePrecedence(leftValue) == GetNodePrecedence(rightValue);
}

int Priority_MoreThanOrEqual(ASTNodeType leftValue, ASTNodeType rightValue)
{
	return Priority_MoreThan(leftValue, rightValue) || Priority_Equal(leftValue, rightValue);
}

int Priority_LessThanOrEqual(ASTNodeType leftValue, ASTNodeType rightValue)
{
	return Priority_LessThan(leftValue, rightValue) || Priority_Equal(leftValue, rightValue);
}