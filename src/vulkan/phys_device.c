#include <stdio.h>
#include <stdlib.h>
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

    size_t used_device = 0;
    for (size_t i = 0; i < device_count; i++) {
        VkPhysicalDeviceProperties dev_properties;
        vkGetPhysicalDeviceProperties(devices[i], &dev_properties);

        LOG(VK, "found device #%zu: %s", i, dev_properties.deviceName);
        if (is_device_sutable(devices[i]) > 0) {
            used_device = i;
            break;
        }
    }

    LOG(VK, "selected device #%zu", used_device);

    return devices[used_device];
}

int is_device_sutable(VkPhysicalDevice device) {

    QueueFamilyIndices indices = find_queue_families(device);

    return indices.graphics_family;
}

QueueFamilyIndices find_queue_families(VkPhysicalDevice device) {
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, NULL);

    VkQueueFamilyProperties queue_families[queue_family_count];
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count,
                                             queue_families);

    QueueFamilyIndices indices = {.graphics_family = 0};

    for (size_t i = 0; i < queue_family_count; i++) {
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphics_family = i;
        }
    }

    return indices;
}
