#pragma once
void PrintErrorf(const char* fmt, ...);

#define PRINT_ON_ALLOC_FAIL(ptr, type, count) \
        PrintErrorf("Failed to allocate memory for %s (%zu bytes)", #ptr, sizeof(type) * (count)); 