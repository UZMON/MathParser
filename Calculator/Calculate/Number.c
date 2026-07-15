#include "Number.h"

double GetNumberAsDecimal(Number n)
{
        return (n.numType == Decimal) ? n.decimal : (double)n.integer;
}