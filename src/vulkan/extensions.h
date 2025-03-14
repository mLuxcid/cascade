#pragma once

#include <stdint.h>

// hold the extension count & names
typedef struct ExtensionList {
    uint32_t count;
    const char **names;
} ExtensionList;

ExtensionList get_instance_extensions(void);
