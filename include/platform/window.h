#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum WindowFlags {
    WINDOW_FLAG_NONE = 0,
    WINDOW_FLAG_NO_VSYNC = 1 << 0,
} WindowFlags;

struct Window;
typedef struct Window Window;

Window *window_create(const char *title, int width, int height, uint32_t flags);
void window_destroy(Window *window);

void window_frame(Window *window);

int window_get_width(const Window *window);
int window_get_height(const Window *window);

bool window_should_close(const Window *window);
void window_set_should_close(Window *window, bool state);

const char *window_get_title(const Window *window);
void window_set_title(Window *window, const char *title);

int window_get_key_state(const Window *window, int key);

/* takes in a `Window *self*, `int width` and a `int height` */
typedef void (*WindowResizeCallback)(Window *, int, int);
void window_set_resize_callback(Window *window, WindowResizeCallback callback);

/* takes in a `Window *self`, int key`, a `int action`, and a `int mods` */
typedef void (*WindowKeyCallback)(Window *, int, int, int);
void window_set_key_callback(Window *window, WindowKeyCallback callback);

