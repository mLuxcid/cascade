#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>

int check_layer_support(const char **layers, uint32_t layer_count);
