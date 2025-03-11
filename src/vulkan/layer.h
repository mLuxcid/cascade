#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <vulkan/vulkan.h>

#ifndef ENABLE_VALIDATION_LAYERS
#define ENABLE_VALIDATION_LAYERS 0
#endif

typedef struct ValidationLayers {
    const char **enabled_layers;
    uint32_t layer_count;
} ValidationLayers;

ValidationLayers *check_layer_support(const char **layers, uint32_t layer_count);
