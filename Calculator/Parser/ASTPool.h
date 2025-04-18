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
/// Creates a new AST node within the specified ASTPool.
/// </summary>
/// <param name="astPool">Pointer to the ASTPool where the node will be allocated.</param>
/// <param name="nodeType">The type of the node (e.g., NodeType_Float, NodeType_Integer, etc.).</param>
/// <param name="position">The source code position associated with the node.</param>
/// <param name="expressionDepth">The depth of the expression, corresponding to the level of nested parentheses.</param>
/// <returns>Pointer to the newly created ASTNode in the ASTPool.</returns>
ASTNode* CreateNode ( ASTPool* astPool , ASTNodeType nodeType , Position position , int expressionDepth );

/// <summary>
/// Creates a new value node within the specified ASTPool.
/// </summary>
/// <param name="astPool">Pointer to the ASTPool where the node will be created. </param>
/// <param name="nodeType"> The type of the node e.g. ( NodeType_Float , NodeType_Integer , ...etc ). </param>
/// <param name="valuePtr">Pointer to the value data (i.e String representing the data).</param>
/// <param name="valueLength">The length of the value data pointed by valuePtr.</param>
/// <param name="position">The source code position associated with the node.</param>
/// <param name="expressionDepth">The depth of the expression, corresponding to the level of nested parentheses.</param>
/// <returns>Pointer to the newly created ASTNode in the ASTPool.</returns>
ASTNode* CreateValueNode ( ASTPool* astPool , ASTNodeType nodeType , const char* valuePtr , size_t valueLength , Position position , int expressionDepth );