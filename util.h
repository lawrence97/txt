#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

/* window */
GLFWwindow *newWindow(int width, int height, char *title);
void destroyWindow(GLFWwindow *window);
