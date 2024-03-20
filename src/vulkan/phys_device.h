#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>

typedef struct _QueueFamilyIndices {
    uint32_t graphics_family;
} QueueFamilyIndices;

VkPhysicalDevice pick_physical_device(VkInstance instance);
QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
