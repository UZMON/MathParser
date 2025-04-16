#pragma once
#include <stddef.h>

#define ASTNodeTypeList \
	AST_NODE_TYPE(NodeType_Float, NodeCategory_Value)  \
	AST_NODE_TYPE(NodeType_Integer, NodeCategory_Value) \
	AST_NODE_TYPE(NodeType_Addition, NodeCategory_Operator) \
	AST_NODE_TYPE(NodeType_Subtraction, NodeCategory_Operator) \
	AST_NODE_TYPE(NodeType_Multiplication, NodeCategory_Operator) \
	AST_NODE_TYPE(NodeType_Division, NodeCategory_Operator) \
	AST_NODE_TYPE(NodeType_Remainder, NodeCategory_Operator) \

//Categories for NodeTypes used to simplify checking for the type of the Node.
typedef enum
{
	NodeCategory_Value ,
	NodeCategory_Operator
}NodeCategory;

//Node Types used in the Abstract Syntax Tree
typedef enum
{
#define AST_NODE_TYPE(ASTNodeTypeName, ASTNodeCategory) ASTNodeTypeName,
	ASTNodeTypeList
#undef AST_NODE_TYPE
	ASTNodeType_Count //Should Always be the last ! 
}ASTNodeType;

//Maps Every ASTNodeType to its corresponding category .
const NodeCategory NodeTypeCategoryTable[ ASTNodeType_Count ];

//The node struct which composes the AST.
typedef struct ASTNode ASTNode;
struct ASTNode
{
	ASTNodeType nodeType;
	union
	{
		//For Value Node Types
		struct 
		{
			const char* valuePtr;
			const size_t length;
		} value;

		//For Operator Node Types
		struct
		{
			ASTNode* left;
			ASTNode* right;
		} op;
	};
};