#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef enum {
	NORMAL,
	EDIT,
} Mode;

typedef struct {
	Mode mode;
	GLFWkeyfun keyptr;
	GLFWcharfun charptr;
} Handler;

void handleKey(GLFWwindow *window, int key, int scancode, int action, int mods);
void handleChar(GLFWwindow *window, unsigned int unicode);
