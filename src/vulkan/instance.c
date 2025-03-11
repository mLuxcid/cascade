#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <vulkan/vulkan.h>

#include "instance.h"
#include "extensions.h"
#include "layer.h"
#include "debug.h"
#include "../log.h"

VkInstance instance_create(void) {
    VkInstance instance;
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

    ValidationLayers *layers =
        check_layer_support(validation_layers, layer_count);
    if (!layers && ENABLE_VALIDATION_LAYERS) {
        ERR("check_layer_support() failed!");
        exit(1);
    }

    VkInstanceCreateInfo instance_create_info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &app_info,
        .enabledExtensionCount = extensions.count,
        .ppEnabledExtensionNames = extensions.names,

    };

    VkDebugUtilsMessengerCreateInfoEXT debug_utils_messenger_create_info = {0};

    if (ENABLE_VALIDATION_LAYERS) {
        populate_debug_messenger_create_info(
            &debug_utils_messenger_create_info);

        instance_create_info.enabledLayerCount = layers->layer_count;
        instance_create_info.ppEnabledLayerNames = layers->enabled_layers;
        instance_create_info.pNext = &debug_utils_messenger_create_info;
    } else {
        instance_create_info.enabledLayerCount = 0;
        instance_create_info.pNext = NULL;
    }

    free(layers == NULL ? layers : layers);

    if (vkCreateInstance(&instance_create_info, NULL, &instance) != VK_SUCCESS) {
        ERR("instance creation failed!");
        exit(1);
    }
    return instance;
}

void instance_destroy(VkInstance instance) {
    vkDestroyInstance(instance, NULL);
}
