#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "window.h"

int is_glfw_initialized = 0;

void window_create(Window *window, size_t w, size_t h, const char *title) {
    if (!is_glfw_initialized) {
        if (!glfwInit()) {
            printf("failed to initialize GLFW.");
            exit(1);
        }
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window->width = w;
    window->height = h;
    window->title = title;
    window->should_close = 0;
    window->window = glfwCreateWindow(w, h, title, NULL, NULL);
    assert(window->window);
}

void window_delete(Window *window) { glfwDestroyWindow(window->window); }
