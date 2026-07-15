#include "ASTNode.h"

const NodeCategory NodeTypeCategoryTable[ASTNodeType_Count] = {
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

const char* NodeNameTable[ASTNodeType_Count] = {
#define AST_NODE_TYPE(ASTNodeTypeName, ASTNodeCategory, Precedence) \
    [ASTNodeTypeName##NodeType] = #ASTNodeTypeName "NodeType",
    ASTNodeTypeList
#undef AST_NODE_TYPE
    /*Expands to :
            [FloatNodeType] = "FloatNodeType" ,
            [IntegerNodeType] = "IntegerNodeType",
            ...etc
    */
};

const int NodeTypePrecedenceTable[ASTNodeType_Count] = {
#define AST_NODE_TYPE(ASTNodeTypeName, ASTNodeCategory, Precedence) \
    [ASTNodeTypeName##NodeType] = Precedence,
    ASTNodeTypeList
#undef AST_NODE_TYPE
};

NodeCategory GetNodeCategory(ASTNodeType type)
{
    return NodeTypeCategoryTable[type];
}

const char* GetNodeName(ASTNodeType type)
{
    return NodeNameTable[type];
}

int GetNodePrecedence(ASTNodeType type)
{
    return NodeTypePrecedenceTable[type];
}

int isLeftAttachable(ASTNodeType nodeType)
{
    if (GetNodeCategory(nodeType) == ValueNodeCategory || GetNodeCategory(nodeType) == NoneNodeCategory)
        return 0;
    return 1;
}

int isRightAttachable(ASTNodeType nodeType)
{
    if (GetNodeCategory(nodeType) == ValueNodeCategory || GetNodeCategory(nodeType) == NoneNodeCategory)
        return 0;
    return 1;
}

int isUnaryCapable(ASTNodeType nodeType)
{
    return nodeType == AdditionNodeType || nodeType == SubtractionNodeType;
}