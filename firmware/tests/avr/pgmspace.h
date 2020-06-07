// Stubs to allow tests to execute AVR code paths

#include <string.h>

size_t strlen_P (const char * s) { return strlen(s); }

void* memcpy_P(void* dest, const void* src, size_t count) { memcpy(dest, src, count); }

#define PSTR(S) (S)