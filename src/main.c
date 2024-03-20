#include <stdio.h>
#include <assert.h>

#include "window.h"
#include "vulkan/instance.h"
#include "vulkan/debug.h"
#include "vulkan/phys_device.h"
#include "log.h"

int main(void) {
    Window window;
    window_create(&window, 800, 600, "Cascade");

    VkInstance instance = NULL;
    instance_create(&instance);
    assert(instance != NULL);

    // setup a debug messenger
    VkDebugUtilsMessengerEXT debug_utils_messenger;
    VkDebugUtilsMessengerCreateInfoEXT debug_utils_messenger_create_info = {0};
    populate_debug_messenger_create_info(&debug_utils_messenger_create_info);

    VkResult res = debug_utils_messenger_create(
        &instance, &debug_utils_messenger_create_info, NULL,
        &debug_utils_messenger);
    if (res != VK_SUCCESS) {
        LOG(VK, "debug_utils_messenger_create() failed with code %d", res);
        return 1;
    }

    // TODO: physical device
    __attribute__((unused)) VkPhysicalDevice physical_device =
        pick_physical_device(instance);
    // TODO: logical device

    while (!window.should_close) {
        if (glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            window.should_close = 1;
        }
        glfwPollEvents();
    }

    debug_utils_messenger_destroy(&instance, debug_utils_messenger, NULL);
    instance_destroy(instance);
    glfwTerminate();
}
