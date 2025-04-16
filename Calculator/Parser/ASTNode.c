#include "ASTNode.h"

const NodeCategory NodeTypeCategoryTable[ASTNodeType_Count] =
{
	#define AST_NODE_TYPE(ASTNodeTypeName, ASTNodeCategory) \
		[ASTNodeTypeName##NodeType] = ASTNodeCategory,
		ASTNodeTypeList
	#undef AST_NODE_TYPE
		/*Expands to :
			[FloatNodeType] = ValueNodeCategory ,
			[IntegerNodeType] = ValueNodeCategory,
			...etc
		*/
};