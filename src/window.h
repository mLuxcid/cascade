#pragma once

#include <GLFW/glfw3.h>
#include <stddef.h>

typedef struct window {
    // GLFW window
    GLFWwindow *window;

    // size
    size_t width;
    size_t height;

    // title
    const char *title;

    int should_close;
} Window;

// create a window with the width of `w`, the height of `h` and a title set
void window_create(Window *window, size_t w, size_t h, const char *title);

// destroy the window & clean up nessecary resources
void window_delete(Window *window);
