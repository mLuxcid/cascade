#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <assert.h>

#include "instance.h"
#include "extensions.h"

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

    VkInstanceCreateInfo instance_create_info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &app_info,
        .enabledExtensionCount = extensions.count,
        .ppEnabledExtensionNames = extensions.names,
        .enabledLayerCount = 0,
    };

    assert(vkCreateInstance(&instance_create_info, NULL, &instance) ==
           VK_SUCCESS);
}

void instance_destroy(VkInstance instance) {
    vkDestroyInstance(instance, NULL);
}
