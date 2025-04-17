#pragma once
#include <stddef.h>
#include "../LexerParserShared/Position.h"

#define NO_PRECEDENCE -1

// Defines a list of AST (Abstract Syntax Tree) node types.
// Each entry has the format:
//     AST_NODE_TYPE(NodeName, NodeCategory, Precedence)
//
// Notes:
//   - Node categories (e.g., ValueNodeCategory, OperatorNodeCategory) are defined separately in the NodeCategory enum.
//   - Precedence is used for operator nodes; use NO_PRECEDENCE for non-operator nodes which is the lowest precedence.
//   - lower precedence value => Higher priority.
#define ASTNodeTypeList \
    AST_NODE_TYPE(None, NoneNodeCategory , NO_PRECEDENCE)  \
    /* Value Nodes */ \
    AST_NODE_TYPE(Integer, ValueNodeCategory , NO_PRECEDENCE) \
    AST_NODE_TYPE(Decimal, ValueNodeCategory , NO_PRECEDENCE)  \
    /* Operator Nodes */ \
    AST_NODE_TYPE(Addition, BinaryNodeCategory , 4) \
    AST_NODE_TYPE(Subtraction, BinaryNodeCategory , 4) \
    AST_NODE_TYPE(Multiplication, BinaryNodeCategory , 3) \
    AST_NODE_TYPE(Division, BinaryNodeCategory , 3) \
    AST_NODE_TYPE(Remainder, BinaryNodeCategory , 3) \


//Categories for NodeTypes ; used to simplify checking for the type of the Node.
typedef enum NodeCategory NodeCategory;
enum NodeCategory
{
	NoneNodeCategory,
	ValueNodeCategory,
	BinaryNodeCategory,
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

//Maps every ASTNodeType to its corresponding category .
const NodeCategory NodeTypeCategoryTable[ ASTNodeType_Count ];
NodeCategory GetNodeCategory ( ASTNodeType type );

//Maps every ASTNodeType to its corresponding precedence.
const int NodeTypePrecedenceTable[ ASTNodeType_Count ];
int GetNodePrecedence ( ASTNodeType type );

//Returns 1 for true , 0 for false
int isLeftAttachable ( ASTNodeType nodeType );
//Returns 1 for true , 0 for false
int isRightAttachable ( ASTNodeType nodeType );

//The node struct which composes the AST.
typedef struct ASTNode ASTNode;
struct ASTNode
{
	ASTNodeType nodeType;
	Position position;
	union
	{
		//For Binary Node Types (Nodes that takes two children in the AST).
		struct
		{
			const ASTNode* leftChild;
			const ASTNode* rightChild;
		} binary;

		//For Value Node Types
		struct 
		{
			const char* valuePtr;
			size_t length;
		} value;
	};
};