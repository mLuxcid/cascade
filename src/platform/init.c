#include <cascade/platform/init.h>
#include <GLFW/glfw3.h>

bool cascade_platform_init(void) {
    static bool is_initialized = false;
    static bool has_error      = false;

    if (!is_initialized) {
        has_error      = glfwInit();
        is_initialized = true;
    }

    return has_error;
}
