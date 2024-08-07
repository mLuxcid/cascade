#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>

void create_logical_device(VkDevice *device, VkPhysicalDevice physical_device);
void destroy_logical_device(VkDevice device);
