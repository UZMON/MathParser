#pragma once
#include "ASTNode.h"
#include "../Constants.h"

typedef struct ASTPool ASTPool;
struct ASTPool
{
	ASTNode nodes[ MAX_AST_NODES ];
	size_t currentIndex;
};

/// <summary>
/// Creates a new value node within the specified ASTPool.
/// </summary>
/// <param name="astPool">Pointer to the ASTPool where the node will be created. </param>
/// <param name="nodeType"> The type of the node e.g. ( NodeType_Float , NodeType_Integer , ...etc ). </param>
/// <param name="valuePtr">Pointer to the value data (i.e String representing the data).</param>
/// <param name="valueLength">The length of the value data pointed by valuePtr.</param>
/// <returns>Pointer to the newly created ASTNode in the ASTPool.</returns>
ASTNode* CreateValueNode ( ASTPool* astPool , ASTNodeType nodeType , const char* valuePtr , size_t valueLength );

/// <summary>
/// Creates a new operator node within the specified ASTPool.
/// </summary>
/// <param name="astPool">Pointer to the ASTPool where the node will be created.</param>
/// <param name="nodeType"> The type of the node e.g. ( NodeType_Addition , NodeType_Subtraction , ...etc ). </param>
/// <param name="left">Pointer to the node at the left side.</param>
/// <param name="right">Pointer to the node at the right side.</param>
/// <returns>Pointer to the newly created ASTNode in the ASTPool.</returns>
ASTNode* CreateOperatorNode ( ASTPool* astPool , ASTNodeType nodeType , const ASTNode* left , const ASTNode* right );