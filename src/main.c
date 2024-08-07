#include <stdio.h>
#include <assert.h>
#include <vulkan/vulkan_core.h>

#include "vulkan/layer.h"
#include "vulkan/logical_device.h"
#include "window.h"
#include "vulkan/instance.h"
#include "vulkan/debug.h"
#include "vulkan/phys_device.h"
#include "log.h"

int main(void) {
    Window *window = NULL;
    window_create(&window, 800, 600, "Cascade");

    VkInstance instance = NULL;
    instance_create(&instance);
    assert(instance != NULL);

    // setup a debug messenger
    VkDebugUtilsMessengerEXT debug_utils_messenger = NULL;
    VkDebugUtilsMessengerCreateInfoEXT debug_utils_messenger_create_info = {0};
    populate_debug_messenger_create_info(&debug_utils_messenger_create_info);

    if (ENABLE_VALIDATION_LAYERS) {
        VkResult res = debug_utils_messenger_create(
            &instance, &debug_utils_messenger_create_info, NULL,
            &debug_utils_messenger);
        if (res != VK_SUCCESS) {
            ERR("debug_utils_messenger_create() failed with code %d", res);
            return 1;
        }
    }

    VkPhysicalDevice physical_device =
        pick_physical_device(instance);
    VkDevice device = NULL;
    create_logical_device(&device, physical_device);
    assert(device != NULL);

    VkQueue graphics_queue = get_logical_device_graphics_queue(device);
    (void)graphics_queue;


    while (!window_should_close(window)) {
        if (window_get_key(window, GLFW_KEY_ESCAPE) == true) {
            window_set_should_close(&window, true);
        }
        window_poll();
    }

    destroy_logical_device(device);

    if (ENABLE_VALIDATION_LAYERS) {
        debug_utils_messenger_destroy(&instance, debug_utils_messenger, NULL);
    }

    instance_destroy(instance);
    window_delete(&window);
}
