#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdbool.h>

/* texture */
GLuint newTexture(char *path);
void destroyTexture(GLuint texture);

/* shader */
GLuint newShader(char *path);
void destroyShader(GLuint shader);

/* window */
GLFWwindow *newWindow(int width, int height, char *title);
void destroyWindow(GLFWwindow *window);

/* logging */
void logRet(int ret, char *func);
int logCompile(GLuint shader);
int logLink(GLuint shader);

/* misc */
char *readFile(char *path);
