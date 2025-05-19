#include <cascade/platform/window.h>
#include <assert.h>
#include <stddef.h>
#include <GLFW/glfw3.h>

static void window_key_callback(struct cascade_window *window,
        int key, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && !mods)
        cascade_window_set_should_close(&window, true);
}

int main(void) {
    struct cascade_window *window = cascade_window_create("example app",
            800, 600, CASCADE_WINDOW_FLAG_VSYNC);
    assert(window != NULL);

    cascade_window_set_key_callback(&window, window_key_callback);

    while (!cascade_window_should_close(window)) {
        cascade_window_frame(window);
    }

    return 0;
}
