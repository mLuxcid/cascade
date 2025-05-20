#include <cascade/platform/window.h>
#include <cascade/platform/init.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

struct cascade_window {
    GLFWwindow *window;

    int         width,
                height;
    const char *title;

    cascade_window_key_callback    key_callback;
    cascade_window_resize_callback resize_callback; 
};

struct cascade_window *cascade_window_create(const char *title,
        int width, int height,
        enum cascade_window_flags flags)
{
    if (!cascade_platform_init()) {
        fprintf(stderr, "failed to initialize platform core.\n");
        abort();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    struct cascade_window *window = calloc(1, sizeof(struct cascade_window));
    if (window == NULL) {
        fprintf(stderr, "failed to allocate memory for window\n");
        abort();
    }

    window->width  = width;
    window->height = height;
    window->title  = title;

    window->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window->window == NULL) {
        fprintf(stderr, "failed to create underlying window object\n");
        abort();
    }

    if (!(flags & CASCADE_WINDOW_FLAG_VSYNC)) {
        glfwSwapInterval(0);
    }

    glfwSetWindowUserPointer(window->window, window);

    /* TODO: check if we are using vulkan */
    glfwMakeContextCurrent(window->window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr,
                "failed to provide required data to the graphics API\n");
        abort();
    }

    return window;
}

void cascade_window_destroy(struct cascade_window *window) {
    if (window == NULL) return;

    glfwDestroyWindow(window->window);
    free(window);
}

void cascade_window_frame(struct cascade_window *window) {
    glfwPollEvents();
    glfwSwapBuffers(window->window);
}

int cascade_window_get_width(const struct cascade_window *window) {
    return window->width;
}

int cascade_window_get_height(const struct cascade_window *window) {
    return window->height;
}

bool cascade_window_should_close(const struct cascade_window *window) {
    return glfwWindowShouldClose(window->window);
}

void cascade_window_set_should_close(struct cascade_window **window, bool state)
{
    glfwSetWindowShouldClose((*window)->window, state);
}

const char *cascade_window_get_title(const struct cascade_window *window) {
    return window->title;
}

void cascade_window_set_title(struct cascade_window **window, const char *title)
{
    (*window)->title = title;
}

int cascade_window_get_key_state(const struct cascade_window *window, int key)
{
    return glfwGetKey(window->window, key);
}

static void _window_resize_callback(GLFWwindow *window, int width, int height) {
    struct cascade_window *self = glfwGetWindowUserPointer(window);

    self->width  = width;
    self->height = height;

    if (self->resize_callback) self->resize_callback(self, width, height);
}

void cascade_window_set_resize_callback(struct cascade_window **window,
        cascade_window_resize_callback callback)
{
    (*window)->resize_callback = callback;
    glfwSetFramebufferSizeCallback((*window)->window, _window_resize_callback);
}

static void _window_key_callback(GLFWwindow *window,
        int key, __attribute__((unused)) int scancode,
        int action, int mods)
{
    struct cascade_window  *self = glfwGetWindowUserPointer(window);
    if (self->key_callback) self->key_callback(self, key, action, mods);
}

void cascade_window_set_key_callback(
        struct cascade_window **window,
        cascade_window_key_callback callback)
{
    (*window)->key_callback = callback;
    glfwSetKeyCallback((*window)->window, _window_key_callback);
}
