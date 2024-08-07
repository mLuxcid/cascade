#include "logical_device.h"
#include "layer.h"
#include "phys_device.h"
#include "../log.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <vulkan/vulkan_core.h>

QueueFamilyIndices indices = {0};

void create_logical_device(VkDevice *device, VkPhysicalDevice physical_device) {
    indices = find_queue_families(physical_device);

    const float queue_priority = 1.0f;
    const VkDeviceQueueCreateInfo queue_create_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = indices.graphics_family,
        .queueCount = 1,
        .pQueuePriorities = &queue_priority,
    };

    // TODO: come back here
    const VkPhysicalDeviceFeatures phys_device_features = {0};

    VkDeviceCreateInfo device_create_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pQueueCreateInfos = &queue_create_info,
        .queueCreateInfoCount = 1,
        .pEnabledFeatures = &phys_device_features,
        .enabledExtensionCount = 0,
        .enabledLayerCount = 0,
    };

    ValidationLayers *layers = check_layer_support(NULL, 0);
    if (ENABLE_VALIDATION_LAYERS) {
        if (layers == NULL) {
            ERR("check_layer_support() failed!");
            exit(1);
        }
        device_create_info.enabledLayerCount = layers->layer_count;
        device_create_info.ppEnabledLayerNames = layers->enabled_layers;
    }
    free(layers);

    if (vkCreateDevice(physical_device, &device_create_info, NULL, device) != VK_SUCCESS) {
        ERR("vkCreateDevice() failed");
        exit(1);
    }
}

VkQueue get_logical_device_graphics_queue(VkDevice device) {
    VkQueue graphics_queue = NULL;
    vkGetDeviceQueue(device, indices.graphics_family, 0, &graphics_queue);
    return graphics_queue;
}

void destroy_logical_device(VkDevice device) {
    vkDestroyDevice(device, NULL);
}
