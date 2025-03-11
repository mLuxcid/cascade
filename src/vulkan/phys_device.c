#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <vulkan/vulkan_core.h>

#include "phys_device.h"
#include "../log.h"

int is_device_sutable(VkPhysicalDevice device);

VkPhysicalDevice pick_physical_device(VkInstance instance) {
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(instance, &device_count, NULL);

    assert(device_count);

    VkPhysicalDevice devices[device_count];

    vkEnumeratePhysicalDevices(instance, &device_count, devices);

    int used_device = -1;
    for (size_t i = 0; i < device_count; i++) {
        VkPhysicalDeviceProperties dev_properties;
        vkGetPhysicalDeviceProperties(devices[i], &dev_properties);

        LOG("found physical device: #%zu: %s", i, dev_properties.deviceName);
        if (is_device_sutable(devices[i]) && used_device == -1) {
            used_device = i;
        }
    }

    if (used_device == -1) {
        ERR("failed to find suitable device");
        exit(1);
    }

    LOG("using physical device #%zu", used_device);

    return devices[used_device];
}

int is_device_sutable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = find_queue_families(device);
    // unreachable index! (unless ur rich or something n got like a custom motherboard to support that many GPUs)
    return indices.graphics_family != UINT32_MAX;
}

QueueFamilyIndices find_queue_families(VkPhysicalDevice device) {
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, NULL);

    VkQueueFamilyProperties queue_families[queue_family_count];
    vkGetPhysicalDeviceQueueFamilyProperties(
        device, &queue_family_count, queue_families
    );

    QueueFamilyIndices indices = {.graphics_family = UINT32_MAX};

    for (size_t i = 0; i < queue_family_count; i++) {
        if (indices.graphics_family != UINT32_MAX) break;
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphics_family = i;
        }
    }

    return indices;
}
