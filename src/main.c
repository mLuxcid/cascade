#include <assert.h>
#include "window.h"
#include "vulkan/instance.h"
#include "vulkan/debug.h"

int main(void) {
    Window window;
    window_create(&window, 800, 600, "Cascade");

    VkInstance instance = NULL;
    instance_create(instance);

    // setup a debug messenger
    VkDebugUtilsMessengerEXT debug_utils_messenger;
    VkDebugUtilsMessengerCreateInfoEXT debug_utils_messenger_create_info = {0};
    populate_debug_messenger_create_info(&debug_utils_messenger_create_info);

    assert(debug_utils_messenger_create(
               instance, &debug_utils_messenger_create_info, NULL,
               &debug_utils_messenger) != VK_SUCCESS);

    while (!window.should_close) {
        if (glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            window.should_close = 1;
        }
        glfwPollEvents();
    }

    instance_destroy(instance);
    glfwTerminate();
}
