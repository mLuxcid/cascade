#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "window.h"
#include "log.h"

struct window_t {
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

void window_create(struct window_t *window, size_t w, size_t h, const char *title) {
    if (!is_glfw_initialized) {
        if (!glfwInit()) {
            ERR(WIN, "failed to initialize GLFW.");
            exit(1);
        }
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window->width = w;
    window->height = h;
    window->title = title;
    window->should_close = false;
    window->window = glfwCreateWindow(w, h, title, NULL, NULL);
    assert(window->window);
}

bool window_should_close(struct window_t *window) {
    return window->should_close;
}

void window_delete(struct window_t *window) { glfwDestroyWindow(window->window); }
