#pragma once

typedef enum NumberType
{
        Integer,
        Decimal
} NumberType;

typedef struct Number
{
        NumberType numType;

        union
        {
                int integer;
                double decimal;
        };
} Number;

double GetNumberAsDecimal(Number n);