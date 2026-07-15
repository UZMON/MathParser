#include "Calculate.h"
#include "../Parser/ASTNode.h"
#include "../Constants.h"
#include "../Utils/ErrorPrinter.h"
#include "Math.h"
#include <stdlib.h>
#include <string.h>

static Number HandleBinaryNode(Number left, Number right, ASTNodeType nodeType, int *error);

Number Calculate(const ASTNode *node, int *error)
{
        if (*error)
                return (Number){.numType = Integer, .integer = 0};

        if (!node)
        {
                PrintErrorf("Internal error: NULL AST node passed to Calculate"); // @Error[Calculate].
                *error = 1;
                return (Number){.numType = Integer, .integer = 0};
        }

        NodeCategory category = GetNodeCategory(node->nodeType);
        if (category == ValueNodeCategory)
        {
                char temp[node->value.length + 1];
                memcpy(temp, node->value.valuePtr, node->value.length);
                temp[node->value.length] = '\0';
                if (node->nodeType == IntegerNodeType)
                {
                        return (Number){
                            .numType = Integer,
                            .integer = (int)strtol(temp, NULL, 10)};
                }
                else if (node->nodeType == DecimalNodeType)
                {
                        return (Number){
                            .numType = Decimal,
                            .decimal = strtod(temp, NULL)};
                }
        }
        else if (category == BinaryNodeCategory)
        {
                Number left = Calculate(node->binary.leftChild, error);
                Number right = Calculate(node->binary.rightChild, error);
                if (*error)
                        return (Number){.numType = Integer, .integer = 0};
                return HandleBinaryNode(left, right, node->nodeType, error);
        }
        else if (category == NoneNodeCategory)
        {
                // Placeholder for a missing operand (e.g. unary "-5" is Subtraction(None, 5)) ; evaluates to 0.
                return (Number){.numType = Integer, .integer = 0};
        }

        PrintErrorf("Internal error: unexpected node type '%s' in Calculate", GetNodeName(node->nodeType)); // @Error[Calculate].
        return (Number){.numType = Integer, .integer = 0};
}

static Number HandleBinaryNode(Number left, Number right, ASTNodeType nodeType, int *error)
{
        switch (nodeType)
        {
        case AdditionNodeType:
                return Addition(left, right, error);
        case SubtractionNodeType:
                return Subtraction(left, right, error);
        case DivisionNodeType:
                return Division(left, right, error);
        case MultiplicationNodeType:
                return Multiplication(left, right, error);
        case RemainderNodeType:
                return Remainder(left, right, error);
        case PowerNodeType:
                return Power(left, right, error);
        default:
                PrintErrorf("Internal error: unexpected node type '%s' in HandleBinaryNode", GetNodeName(nodeType)); // @Error[Calculate].
                return (Number){.numType = Integer, .integer = 0};
        }
}