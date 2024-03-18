#pragma once

#include <vulkan/vulkan.h>

VkResult debug_utils_messenger_create(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *p_create_info,
    const VkAllocationCallbacks *p_allocator,
    VkDebugUtilsMessengerEXT *p_debug_messenger);

void debug_utils_messenger_destroy(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debug_messenger,
                                   const VkAllocationCallbacks *p_allocator);

void populate_debug_messenger_create_info(
    VkDebugUtilsMessengerCreateInfoEXT *create_info);
