#pragma once

#include <vulkan/vulkan.h>
#include <stdbool.h>

VkInstance instance_create(void);
void instance_destroy(VkInstance instance);
