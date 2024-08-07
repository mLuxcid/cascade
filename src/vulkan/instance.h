#pragma once

#include <vulkan/vulkan.h>
#include <stdbool.h>

void instance_create(VkInstance *instance);
void instance_destroy(VkInstance instance);
