#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

const char *log_color[] = {
    ['E'] = "\033[31m",
    ['L'] = "",
    ['W'] = "\033[33m"
};

void log_write(
    const char *restrict file,
    int ln,
    const char *restrict fn,
    const char *restrict prefix,
    const char *restrict fmt,
    ...
) {
    va_list args;
    va_start(args, fmt);
    FILE *fp = !strncmp(prefix, "LOG", 3) ? stdout : stderr;

    // evil fuckery
    fprintf(fp, "%s[%s:%d][%s] ", log_color[(int)prefix[0]], file, ln, fn);

    char buf[4096];
    const int len = vsnprintf(buf, sizeof(buf), fmt, args);
    fprintf(fp, "%s%s", buf, buf[len] == '\n' ? "\033[0m" : "\n\033[0m");
    va_end(args);
}
