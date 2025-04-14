#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "Constants.h"
#include "Lexer/Lexer.h"
int main()
{
	printf("Welcome To Calculator !\n");
	printf("Enter your expression: \n");
	char expression[MAX_EXPRESSION_SIZE];
	fgets(expression, sizeof(expression), stdin);
	expression[MAX_EXPRESSION_SIZE - 1] = '\0';
	InitSymbolsTable();
	Token tokens[MAX_EXPRESSION_SIZE];
	size_t tokensCount = 0;
	int error = 0;
	 Lex(expression,tokens,&tokensCount,&error);
	 if (error)
	 {
		 return error;
	 }

	for (int i = 0; i < tokensCount; i++)
	{
		for (int j = 0; j < tokens[i].length; j++)
		{
			char character = tokens[i].valuePtr[j];
			printf("%c",character);
		}
		printf("\n");
	}
}