#ifndef SNPRINTF_H
#define SNPRINTF_H

#include <stddef.h>
// int vsnprintf(char *s, size_t n, const char *fmt, va_list args);
int snprintf(char *s, size_t n, const char *fmt, ...);
int print(const char *fmt, ...);

#endif
