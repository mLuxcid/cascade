#pragma once

void log_write(
    const char *restrict file,
    int ln,
    const char *restrict fn,
    const char *restrict prefix,
    const char *restrict fmt,
    ...);

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

#define LOG(fmt, ...)                                                          \
    log_write(__FILE__, __LINE__, __FUNCTION__, "LOG", fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)                                                         \
    log_write(__FILE__, __LINE__, __FUNCTION__, "WRN", fmt, ##__VA_ARGS__)
#define ERR( fmt, ...)                                                         \
    log_write(__FILE__, __LINE__, __FUNCTION__, "ERR", fmt, ##__VA_ARGS__)

#pragma clang diagnostic pop

#endif
