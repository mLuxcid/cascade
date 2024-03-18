#include "vulkan/instance.h"
#include "window.h"

int main(void) {
    Window window;
    window_create(&window, 800, 600, "Cascade");

    VkInstance instance = NULL;
    instance_create(instance);

    while (!window.should_close) {
        if (glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            window.should_close = 1;
        }
        glfwPollEvents();
    }

    instance_destroy(instance);
    glfwTerminate();
}
