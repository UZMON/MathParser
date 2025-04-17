#include "ASTNode.h"

const NodeCategory NodeTypeCategoryTable[ASTNodeType_Count] =
{
	#define AST_NODE_TYPE(ASTNodeTypeName, ASTNodeCategory, Precedence) \
		[ASTNodeTypeName##NodeType] = ASTNodeCategory,
		ASTNodeTypeList
	#undef AST_NODE_TYPE
		/*Expands to :
			[FloatNodeType] = ValueNodeCategory ,
			[IntegerNodeType] = ValueNodeCategory,
			...etc
		*/
};
const int NodeTypePrecedenceTable[ASTNodeType_Count] =
{
		#define AST_NODE_TYPE(ASTNodeTypeName, ASTNodeCategory, Precedence) \
		[ASTNodeTypeName##NodeType] = Precedence,
		ASTNodeTypeList
	#undef AST_NODE_TYPE
};

NodeCategory GetNodeCategory(ASTNodeType type) 
{
	return NodeTypeCategoryTable[type];
}

int GetNodePrecedence(ASTNodeType type)
{
	return NodeTypePrecedenceTable[type];
}

int isLeftAttachable(ASTNodeType nodeType)
{
	if (GetNodeCategory(nodeType) == ValueNodeCategory)
		return 0;
	return 1;
}

int isRightAttachable(ASTNodeType nodeType)
{
	if (GetNodeCategory(nodeType) == ValueNodeCategory)
		return 0;
	return 1;
}