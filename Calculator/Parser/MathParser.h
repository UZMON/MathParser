#pragma once
#include <stddef.h>
#include "../LexerParserShared/Token.h"
#include "../Constants.h"
#include "ASTNode.h"

void ParseMathTokens ( Token* tokens , size_t tokensCount );

ASTNode* CreateValueNode ( ASTNodeType nodeType , const char* valuePtr , size_t valuelength );