#pragma once
#include "../Parser/ASTNode.h"
#include "Number.h"

Number Calculate(const ASTNode *node, int *error);