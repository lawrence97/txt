#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdbool.h>

GLuint newTexture(char *path);
void destroyTexture(GLuint texture);

GLuint newShader(char *path);
void destroyShader(GLuint shader);

GLFWwindow *newWindow(int width, int height, char *title);
void destroyWindow(GLFWwindow *window);

void logRet(int ret, char *func);
int logCompile(GLuint shader);
int logLink(GLuint shader);

char *readFile(char *path);
