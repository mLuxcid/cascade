#include <platform/window.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

struct Window {
    GLFWwindow *window;

    int width, height;
    const char *title;
};

Window *window_create(const char *title, int width, int height, uint32_t flags)
{
    Window *win = calloc(1, sizeof(Window));
    if (win == NULL) {
        fprintf(stderr, "failed to allocate memory for window");
        abort();
    }

    win->width = width;
    win->height = height;
    win->title = title;

    win->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (win->window == NULL) {
        fprintf(stderr, "failed to create underlying window object");
    }

    if (flags & WINDOW_FLAG_NO_VSYNC) {
        glfwSwapInterval(0);
    }

    return win;
}

void window_destroy(Window *window) {
    if (window == NULL) return;

    glfwDestroyWindow(window->window);
    free(window);
}

void window_frame(Window *window) {
    glfwPollEvents();
    glfwSwapBuffers(window->window);
}

int window_get_width(const Window *window) {
    return window->width;
}

int window_get_height(const Window *window) {
    return window->height;
}

bool window_should_close(const Window *window) {
    return glfwWindowShouldClose(window->window);
}

void window_set_should_close(Window *window, bool state) {
    glfwSetWindowShouldClose(window->window, state);
}

const char *window_get_title(const Window *window) {
    return window->title;
}

void window_set_title(Window *window, const char *title) {
    window->title = title;
}

int window_get_key_state(const Window *window, int key) {
    return glfwGetKey(window->window, key);
}

/* TODO: implement this */
void window_set_resize_callback(Window *window, WindowResizeCallback callback) {
    (void)window;
    (void)callback;
}

/* TODO: implement this */
void window_set_key_callback(Window *window, WindowKeyCallback callback) {
    (void)window;
    (void)callback;
}
