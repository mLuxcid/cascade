#pragma once

#define LOG(prefix, fmt, ...) printf(#prefix " : " fmt "\n", ##__VA_ARGS__)
#define WARN(prefix, fmt, ...)                                                 \
    printf("\033[33m" #prefix " : " fmt "\033[0m\n", ##__VA_ARGS__)
#define ERR(prefix, fmt, ...)                                                  \
    printf("\033[31m" #prefix " : " fmt "\033[0m\n", ##__VA_ARGS__);
