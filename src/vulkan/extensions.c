#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extensions.h"
#include "../log.h"

extern int enable_validation_layers;

ExtensionList get_instance_extensions(void) {
    ExtensionList list = {
        .count = 0,
    };
    list.names = glfwGetRequiredInstanceExtensions(&list.count);

    uint32_t available_extension_count = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &available_extension_count,
                                           NULL);

    if (enable_validation_layers) {
        list.names[list.count++] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    }

    VkExtensionProperties available_extensions[available_extension_count];
    vkEnumerateInstanceExtensionProperties(NULL, &available_extension_count,
                                           available_extensions);

    int found[list.count];
    LOG(VK, "available extensions:");
    for (size_t i = 0; i < available_extension_count; i++) {

        for (size_t j = 0; j < list.count; j++) {
            if (!strcmp(list.names[j], available_extensions[i].extensionName)) {
                found[j] = 1;
                break;
            }
        }

        LOG(VK, "\t%s", available_extensions[i].extensionName);
    }

    for (size_t i = 0; i < list.count; i++) {
        if (!found[i]) {
            ERR(VK, "GLFW requires unavailable extension: %s", list.names[i]);
            exit(1);
        }
    }

    return list;
}
