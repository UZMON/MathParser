#include "Constants.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Calculate/Calculate.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void PrintAST(const ASTNode *node);

int main()
{
        printf("Welcome To Calculator !\n");
        printf("Type an expression to evaluate it, or 'exit' to quit.\n");

        InitLexer();

        char expression[MAX_EXPRESSION_SIZE];
        while (1)
        {
                // Read Input ===================================================================================================================
                printf("\n> ");
                if (!fgets(expression, sizeof(expression), stdin))
                {
                        printf("\n");
                        break; // EOF (e.g. Ctrl+D) ; exit gracefully.
                }
                expression[MAX_EXPRESSION_SIZE - 1] = '\0';

                size_t length = strlen(expression);
                if (length > 0 && expression[length - 1] == '\n')
                        expression[--length] = '\0';

                if (length == 0)
                        continue; // Blank line ; just re-prompt.

                if (strcmp(expression, "exit") == 0 || strcmp(expression, "quit") == 0)
                        break;

                // Lexing ========================================================================================================================
                Token tokens[MAX_EXPRESSION_SIZE];
                size_t tokensCount = 0;
                int error = 0;
                Lex(expression, tokens, &tokensCount, &error);
                if (error)
                        continue;

                // Parsing =======================================================================================================================
                ASTPool pool = {0};
                ASTNodeStack stack = {0};
                TokenArray tokenArr = {.tokens = tokens, .length = tokensCount};
                error = ParseTokensToStack(tokenArr, &pool, &stack);
                if (error)
                        continue;

                // Output ========================================================================================================================
                ASTNode *AST = PopASTStack(&stack);
                if (!AST)
                {
                        fprintf(stderr, "Internal error: empty AST after parsing.\n");
                        continue;
                }
                PrintAST(AST);
                Number result = Calculate(AST, &error);
                if (error)
                        continue;

                if (result.numType == Integer)
                {
                        printf("Answer: %d\n", result.integer);
                }
                else if (result.numType == Decimal)
                {
                        printf("Answer: %.15g\n", result.decimal);
                }
        }

        printf("Goodbye!\n");
        return 0;
}

static void PrintAST_Internal(const ASTNode *node, const char *prefix, int isLast)
{
        if (!node)
                return;

        // Print current node with tree lines
        printf("%s%s", prefix, isLast ? "|___ " : "|--- ");

        if (GetNodeCategory(node->nodeType) == ValueNodeCategory)
        {
                printf("%s :", GetNodeName(node->nodeType));
                printf("%.*s (depth: %d)\n", (int)node->value.length, node->value.valuePtr, node->expressionDepth);
        }
        else
        {
                printf("%s (depth: %d)\n", GetNodeName(node->nodeType), node->expressionDepth);
        }

        // Prepare new prefix for children
        char newPrefix[256];
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "| ");

        // Recursively print children (left then right)
        if (GetNodeCategory(node->nodeType) == BinaryNodeCategory)
        {
                PrintAST_Internal(node->binary.leftChild, newPrefix, 0);
                PrintAST_Internal(node->binary.rightChild, newPrefix, 1);
        }
}

static void PrintAST(const ASTNode *root)
{
        PrintAST_Internal(root, "", 1);
}