#pragma once

#include "func.h"

#define NUM_KEYBINDS 3

typedef struct {
	int key;
	int mods;
	Func ptr;
} Keybind;

Keybind keybinds[NUM_KEYBINDS] = {
	{.key = GLFW_KEY_ESCAPE, .mods = 0, .ptr = funcQuit},
	{.key = GLFW_KEY_TAB, .mods = 0, .ptr = funcPrint},
	{.key = GLFW_KEY_I, .mods = GLFW_MOD_SHIFT, .ptr = funcEdit},
};
