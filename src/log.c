#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void log_write(
    const char *restrict file,
    int ln,
    const char *restrict fn,
    const char *restrict prefix,
    const char *restrict fmt,
    ...) {
    va_list args;
    va_start(args, fmt);
    FILE *fp = !strcmp(prefix, "LOG") ? stdout : stderr;
    fprintf(fp, "%s[%s:%d][%s] ",
        !strcmp(prefix, "WRN")
            ? "\033[33m" : !strcmp(prefix, "ERR") ? "\033[31m" : "",
        file, ln, fn);

    char buf[4096];
    const int len = vsnprintf(buf, sizeof(buf), fmt, args);
    fprintf(fp, "%s%s", buf, buf[len] == '\n' ? "\033[0m" : "\n\033[0m");
    va_end(args);
}