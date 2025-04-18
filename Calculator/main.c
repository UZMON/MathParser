#include "Constants.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void PrintAST(const ASTNode* node);

int main()
{
    // Read Input ===========================================================================================================================
    printf("Welcome To Calculator !\n");
    printf("Enter your expression: \n");
    char expression[MAX_EXPRESSION_SIZE];
    fgets(expression, sizeof(expression), stdin);
    expression[MAX_EXPRESSION_SIZE - 1] = '\0';

    // Lexing ==============================================================================================================================
    Token tokens[MAX_EXPRESSION_SIZE];
    size_t tokensCount = 0;
    int error = 0;
    InitLexer();
    Lex(expression, tokens, &tokensCount, &error);
    if (error)
        return error;

    // Parsing ==============================================================================================================================
    ASTPool pool = { 0 };
    ASTNodeStack stack = { 0 };
    TokenArray tokenArr = { .tokens = tokens, .length = tokensCount };
    error = ParseTokensToStack(tokenArr, &pool, &stack);
    if (error)
        return error;

    // Output ==========================================================================================================================
    ASTNode* AST = PopASTStack(&stack);
    PrintAST(AST);
}

// TODO clean here.
// 6 + 5.5 * ((3-8) + 2.1)%4

// !!! Chatgpt wrote this function because I am lazy and noob. !!!
static void PrintAST_Internal(const ASTNode* node, const char* prefix, int isLast)
{
    if (!node)
        return;

    // Print current node with tree lines
    printf("%s%s", prefix, isLast ? "|___ " : "|--- ");

    if (GetNodeCategory(node->nodeType) == ValueNodeCategory) {
        printf("%s :", GetNodeName(node->nodeType));
        printf("%.*s (depth: %d)\n", (int)node->value.length, node->value.valuePtr, node->expressionDepth);
    } else {
        printf("%s (depth: %d)\n", GetNodeName(node->nodeType), node->expressionDepth);
    }

    // Prepare new prefix for children
    char newPrefix[256];
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "| ");

    // Recursively print children (left then right)
    if (GetNodeCategory(node->nodeType) == BinaryNodeCategory) {
        PrintAST_Internal(node->binary.leftChild, newPrefix, 0);
        PrintAST_Internal(node->binary.rightChild, newPrefix, 1);
    }
}

static void PrintAST(const ASTNode* root)
{
    PrintAST_Internal(root, "", 1);
}