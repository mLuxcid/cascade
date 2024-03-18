#include <stdio.h>
#include <assert.h>
#include <vulkan/vulkan.h>

#include "instance.h"
#include "extensions.h"
#include "layer.h"
#include "debug.h"

int enable_validation_layers = 1;

void instance_create(VkInstance instance) {
    VkApplicationInfo app_info = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "cascade",
        .applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
        .pEngineName = "cascade",
        .engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
        .apiVersion = VK_API_VERSION_1_3,
    };

    ExtensionList extensions = get_instance_extensions();

    const char *validation_layers[] = {
        "VK_LAYER_KHRONOS_validation",
    };

    uint32_t layer_count =
        sizeof(validation_layers) / sizeof(validation_layers[0]);

    assert(check_layer_support(validation_layers, layer_count) &&
           enable_validation_layers);

    VkInstanceCreateInfo instance_create_info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &app_info,
        .enabledExtensionCount = extensions.count,
        .ppEnabledExtensionNames = extensions.names,

    };

    VkDebugUtilsMessengerCreateInfoEXT debug_utils_messenger_create_info = {0};

    if (enable_validation_layers) {
        populate_debug_messenger_create_info(
            &debug_utils_messenger_create_info);

        instance_create_info.enabledLayerCount = layer_count;
        instance_create_info.ppEnabledLayerNames = validation_layers;
        instance_create_info.pNext = &debug_utils_messenger_create_info;
    } else {
        instance_create_info.enabledLayerCount = 0;
        instance_create_info.pNext = NULL;
    }

    assert(vkCreateInstance(&instance_create_info, NULL, &instance) ==
           VK_SUCCESS);
}

void instance_destroy(VkInstance instance) {
    vkDestroyInstance(instance, NULL);
}
