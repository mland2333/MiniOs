#pragma once
#include <stdarg.h>

int printf(const char* fmt, ...);
int sprintf(char* str, const char* fmt, ...);
int vprintf(const char *fmt, va_list ap);
void panic(const char *s);
