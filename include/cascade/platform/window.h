#pragma once

#include <stdbool.h>
#include <stdint.h>

enum cascade_window_flags {
    CASCADE_WINDOW_FLAG_VSYNC = 1 << 0,
};

struct cascade_window;

struct cascade_window *cascade_window_create(const char *title,
        int width, int height,
        enum cascade_window_flags flags);
void cascade_window_destroy(struct cascade_window *window);

void cascade_window_frame(struct cascade_window *window);

int cascade_window_get_width(const struct cascade_window *window);
int cascade_window_get_height(const struct cascade_window *window);

bool cascade_window_should_close(const struct cascade_window *window);
void cascade_window_set_should_close(struct cascade_window **window, bool state);

const char *cascade_window_get_title(const struct cascade_window *window);
void cascade_window_set_title(struct cascade_window **window, const char *title);

int cascade_window_get_key_state(const struct cascade_window *window, int key);

/* takes in a `struct cascade_window *self*, `int width` and a `int height` */
typedef void (*cascade_window_resize_callback)
    (struct cascade_window *, int, int);

void cascade_window_set_resize_callback(struct cascade_window **window,
        cascade_window_resize_callback callback);

/* takes in a `struct cascade_window *self`, int key`, a `int action`, and a `int mods` */
typedef void (*cascade_window_key_callback)
    (struct cascade_window *, int, int, int);

void cascade_window_set_key_callback(struct cascade_window **window,
        cascade_window_key_callback callback);

