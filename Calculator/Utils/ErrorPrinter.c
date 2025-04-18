#include "ErrorPrinter.h"
#include <stdarg.h>
#include <stdio.h>

void PrintErrorf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}