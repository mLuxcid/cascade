#pragma once

#include <vulkan/vulkan.h>
#include <stdbool.h>

bool are_layers_enabled(void);

void instance_create(VkInstance *instance);
void instance_destroy(VkInstance instance);
