#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* fmt, ...);
int sprintf(char* str, const char* fmt, ...);
int vprintf(const char *fmt, va_list ap);

#ifdef __cplusplus
}
#endif
