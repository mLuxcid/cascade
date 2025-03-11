#pragma once

#include <GLFW/glfw3.h>
#include <stddef.h>
#include <stdbool.h>

struct Window;
typedef struct Window Window;

// create a window_t with the width of `w`, the height of `h` and a title set
Window *window_create(size_t w, size_t h, const char *title);

bool window_should_close(Window *window);
void window_set_should_close(Window **window, bool value);

bool window_get_key(Window *window_t, int glfw_key_code);

void window_poll(void);

// destroy the window_t & clean up nessecary resources
void window_delete(Window **window);
