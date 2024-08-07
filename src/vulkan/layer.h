#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <vulkan/vulkan.h>

typedef struct {
    const char **enabled_layers;
    uint32_t layer_count;
} ValidationLayers;

ValidationLayers *check_layer_support(const char **layers, uint32_t layer_count);
