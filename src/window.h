#pragma once

#include <GLFW/glfw3.h>
#include <stddef.h>
#include <stdbool.h>

struct window_t;

// create a window with the width of `w`, the height of `h` and a title set
void window_create(struct window_t **window, size_t w, size_t h, const char *title);

bool window_should_close(struct window_t *window);
void window_set_should_close(struct window_t **window, bool value);

// destroy the window & clean up nessecary resources
void window_delete(struct window_t **window);
