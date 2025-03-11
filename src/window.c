#include <errno.h> // IWYU pragma: keep
#include <string.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "window.h"
#include "log.h"

struct Window {
    // GLFW window
    GLFWwindow *window;

    // size
    size_t width;
    size_t height;

    // title
    const char *title;

    bool should_close;
};


int is_glfw_initialized = 0;

Window *window_create(size_t w, size_t h, const char *title) {
    if (!is_glfw_initialized) {
        if (!glfwInit()) {
            ERR("failed to initialize GLFW.");
            exit(1);
        }
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


    Window *window = calloc(1, sizeof(Window));
    if (window == NULL) {
        ERR("calloc() failed: %s", strerror(errno));
    }

    window->width = w;
    window->height = h;
    window->title = title;
    window->should_close = false;
    window->window = glfwCreateWindow(w, h, title, NULL, NULL);
    assert(window->window);
    return window;
}

bool window_should_close(Window *window) {
    return window->should_close;
}

void window_set_should_close(Window **window, bool val) {
    (*window)->should_close = val;
}

bool window_get_key(Window *window, int glfw_key_code) {
    return glfwGetKey(window->window, glfw_key_code);
}

void window_poll(void) {
    glfwPollEvents();
}

void window_delete(Window **window) {
    glfwDestroyWindow((*window)->window);
    free(*window);
    glfwTerminate();
}
