#pragma once

#include <GLFW/glfw3.h>
#include <stddef.h>
#include <stdbool.h>

struct window_t;
typedef struct window_t Window;

// create a window with the width of `w`, the height of `h` and a title set
void window_create(Window **window, size_t w, size_t h, const char *title);

bool window_should_close(Window *window);
void window_set_should_close(Window **window, bool value);

bool window_get_key(Window *window, int glfw_key_code);

void window_poll(void);

// destroy the window & clean up nessecary resources
void window_delete(Window **window);
