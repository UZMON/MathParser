#include "ASTNode.h"

const NodeCategory NodeTypeCategoryTable[ASTNodeType_Count] =
{
	#define AST_NODE_TYPE(ASTNodeTypeName, ASTNodeCategory) \
		[ASTNodeTypeName] = ASTNodeCategory,
		ASTNodeTypeList
	#undef AST_NODE_TYPE
		/*Expands to :
			[NodeType_Float] = NodeCategory_Value ,
			[NodeType_Integer] = NodeCategory_Value,
			...etc
		*/
};