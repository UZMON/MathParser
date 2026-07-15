#include "Math.h"
#include "../Utils/ErrorPrinter.h"
#include <math.h>
#include <limits.h>

static void ReportOverflow(int* error)
{
        PrintErrorf("Arithmetic overflow"); // @Error[Math].
        *error = 1;
}

Number Addition(Number first, Number second, int* error)
{
        Number result;
        if (first.numType == Integer && second.numType == Integer)
        {
                if ((second.integer > 0 && first.integer > INT_MAX - second.integer) ||
                    (second.integer < 0 && first.integer < INT_MIN - second.integer))
                {
                        ReportOverflow(error);
                        return (Number){.numType = Integer, .integer = 0};
                }
                result.numType = Integer;
                result.integer = first.integer + second.integer;
                return result;
        }
        result.numType = Decimal;
        result.decimal = GetNumberAsDecimal(first) + GetNumberAsDecimal(second);
        return result;
}

Number Subtraction(Number first, Number second, int* error)
{
        Number result;
        if (first.numType == Integer && second.numType == Integer)
        {
                if ((second.integer < 0 && first.integer > INT_MAX + second.integer) ||
                    (second.integer > 0 && first.integer < INT_MIN + second.integer))
                {
                        ReportOverflow(error);
                        return (Number){.numType = Integer, .integer = 0};
                }
                result.numType = Integer;
                result.integer = first.integer - second.integer;
                return result;
        }
        result.numType = Decimal;
        result.decimal = GetNumberAsDecimal(first) - GetNumberAsDecimal(second);
        return result;
}

Number Division(Number first, Number second, int* error)
{
        Number result;
        if (first.numType == Integer && second.numType == Integer)
        {
                if (second.integer == 0)
                {
                        PrintErrorf("Division by zero"); // @Error[Math].
                        *error = 1;
                        return (Number){.numType = Integer, .integer = 0};
                }
                if (first.integer == INT_MIN && second.integer == -1)
                {
                        // INT_MIN / -1 overflows int (and traps on some hardware, e.g. x86 IDIV).
                        ReportOverflow(error);
                        return (Number){.numType = Integer, .integer = 0};
                }
                result.numType = Integer;
                result.integer = first.integer / second.integer;
                return result;
        }
        double divisor = GetNumberAsDecimal(second);
        if (divisor == 0.0)
        {
                PrintErrorf("Division by zero"); // @Error[Math].
                *error = 1;
                return (Number){.numType = Integer, .integer = 0};
        }
        result.numType = Decimal;
        result.decimal = GetNumberAsDecimal(first) / divisor;
        return result;
}

Number Multiplication(Number first, Number second, int* error)
{
        Number result;
        if (first.numType == Integer && second.numType == Integer)
        {
                long long product = (long long)first.integer * (long long)second.integer;
                if (product > INT_MAX || product < INT_MIN)
                {
                        ReportOverflow(error);
                        return (Number){.numType = Integer, .integer = 0};
                }
                result.numType = Integer;
                result.integer = (int)product;
                return result;
        }
        result.numType = Decimal;
        result.decimal = GetNumberAsDecimal(first) * GetNumberAsDecimal(second);
        return result;
}

Number Remainder(Number first, Number second, int* error)
{
        Number result;
        if (first.numType == Integer && second.numType == Integer)
        {
                if (second.integer == 0)
                {
                        PrintErrorf("Division by zero"); // @Error[Math].
                        *error = 1;
                        return (Number){.numType = Integer, .integer = 0};
                }
                if (first.integer == INT_MIN && second.integer == -1)
                {
                        // INT_MIN % -1 is mathematically 0, but the CPU computes it via the
                        // same trapping instruction as INT_MIN / -1 ; special-case it instead.
                        result.numType = Integer;
                        result.integer = 0;
                        return result;
                }
                result.numType = Integer;
                result.integer = first.integer % second.integer;
                return result;
        }
        double divisor = GetNumberAsDecimal(second);
        if (divisor == 0.0)
        {
                PrintErrorf("Division by zero"); // @Error[Math].
                *error = 1;
                return (Number){.numType = Integer, .integer = 0};
        }
        result.numType = Decimal;
        result.decimal = fmod(GetNumberAsDecimal(first), divisor);
        return result;
}

static int ipow(int base, int exp, int* overflow)
{
        long long result = 1;
        long long b = base;
        for (;;)
        {
                if (exp & 1)
                {
                        result *= b;
                        if (result > INT_MAX || result < INT_MIN)
                        {
                                *overflow = 1;
                                return 0;
                        }
                }
                exp >>= 1;
                if (!exp)
                        break;
                b *= b;
                if (b > INT_MAX || b < INT_MIN)
                {
                        *overflow = 1;
                        return 0;
                }
        }
        return (int)result;
}

Number Power(Number first, Number second, int* error)
{
        Number result;
        if (first.numType == Integer && second.numType == Integer && second.integer >= 0)
        {
                int overflow = 0;
                int value = ipow(first.integer, second.integer, &overflow);
                if (overflow)
                {
                        ReportOverflow(error);
                        return (Number){.numType = Integer, .integer = 0};
                }
                result.numType = Integer;
                result.integer = value;
                return result;
        }
        result.numType = Decimal;
        result.decimal = pow(GetNumberAsDecimal(first), GetNumberAsDecimal(second));
        return result;
}
