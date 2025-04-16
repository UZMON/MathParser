#pragma once
#include <stddef.h>

// Defines a list of Node types that composes the AST (Abstract syntax tree).
// Format:
//     AST_NODE_TYPE(NodeName, NodeCategory)
//Note:
//		Node categories (like ValueNodeCategory, OperatorNodeCategory) are defined separately in NodeCategory enum.
#define ASTNodeTypeList \
	AST_NODE_TYPE(None, NoneNodeCategory)  \
	/* Value Nodes */ \
	AST_NODE_TYPE(Integer, ValueNodeCategory) \
	AST_NODE_TYPE(Decimal, ValueNodeCategory)  \
	/* Operator Nodes */ \
	AST_NODE_TYPE(Addition, OperatorNodeCategory) \
	AST_NODE_TYPE(Subtraction, OperatorNodeCategory) \
	AST_NODE_TYPE(Multiplication, OperatorNodeCategory) \
	AST_NODE_TYPE(Division, OperatorNodeCategory) \
	AST_NODE_TYPE(Remainder, OperatorNodeCategory) \

//Categories for NodeTypes ; used to simplify checking for the type of the Node.
typedef enum NodeCategory NodeCategory;
enum NodeCategory
{
	NoneNodeCategory,
	ValueNodeCategory,
	OperatorNodeCategory,
	NodeCategory_Count //This should always be the last one.
};

//Node Types used in the Abstract Syntax Tree
typedef enum ASTNodeType ASTNodeType;
enum ASTNodeType
{
#define AST_NODE_TYPE(ASTNodeTypeName, ASTNodeCategory) ASTNodeTypeName##NodeType,
	ASTNodeTypeList
#undef AST_NODE_TYPE
	ASTNodeType_Count //Should Always be the last ! 
};

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
			size_t length;
		} value;

		//For Operator Node Types
		struct
		{
			const ASTNode* left;
			const ASTNode* right;
		} op;
	};
};