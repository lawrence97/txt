#include <stb_image.h>

#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "util.h"

GLuint newTexture(char *path) {

	int w, h, n;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc *pixels = stbi_load(path, &w, &h, &n, 0);
	if (pixels == NULL) {
		return 0;
	}

	if (PRINT == true) {
		printf("texture %s w: %d, h: %d.\n", path, w, h);
	}

	GLuint tex = 0;

	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	stbi_image_free(pixels);
	pixels = NULL;

	return tex;
}

void destroyTexture(GLuint texture) {

	glDeleteTextures(1, &texture);

	return;
}

GLuint newShader(char *path) {

	char *glslSource = readFile(path);
	if (glslSource == NULL) {
		return 0;
	}

	char *vPrefix = "#version 330 core\n#define VERTEX\n";
	char *fPrefix = "#version 330 core\n#define FRAGMENT\n";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	const char *source[2] = {NULL, glslSource};
	source[0] = vPrefix;
	glShaderSource(vs, 2, source, NULL);
	source[0] = fPrefix;
	glShaderSource(fs, 2, source, NULL);

	free(glslSource);
	glslSource = NULL;

	glCompileShader(vs);
	glCompileShader(fs);

	if (logCompile(vs) < 0 || logCompile(fs) < 0) {
		glDeleteShader(vs);
		glDeleteShader(fs);
		return 0;
	}

	GLuint program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	glDetachShader(program, vs);
	glDetachShader(program, fs);

	glDeleteShader(vs);
	glDeleteShader(fs);

	if (logLink(program) < 0) {
		glDeleteProgram(program);
		return 0;
	}

	glUseProgram(program);

	return program;
}

void destroyShader(GLuint shader) {

	glDeleteProgram(shader);

	return;
}

GLFWwindow *newWindow(int width, int height, char *title) {

	if (glfwInit() == 0) {
		return NULL;
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
		glfwTerminate();
		return NULL;
	}

	return window;
}

void destroyWindow(GLFWwindow *window) {

	glfwDestroyWindow(window);
	glfwTerminate();

	return;
}

void logRet(int ret, char *func) {

	fprintf(stderr, "err: %d returned from %s.\n", ret, func);

	return;
}

int logCompile(GLuint shader) {

	int status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == 0) {
		char log[600];
		int len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		glGetShaderInfoLog(shader, len, &len, log);
		fprintf(stderr, "\n%s\n", log);
		return -1;
	}

	return 0;
}

int logLink(GLuint shader) {

	int status = 0;
	glGetProgramiv(shader, GL_LINK_STATUS, &status);
	if (status == 0) {
		char log[600];
		int len = 0;
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &len);
		glGetProgramInfoLog(shader, len, &len, log);
		fprintf(stderr, "\n%s\n", log);
		return -1;
	}

	return 0;
}

char *readFile(char *path) {

	FILE *f = fopen(path, "rb");
	if (f == NULL) {
		return NULL;
	}

	fseek(f, 0l, SEEK_END);
	size_t capacity = ftell(f);
	fseek(f, 0l, SEEK_SET);

	char *str = calloc(sizeof(char), capacity);
	if (str == NULL) {
		fclose(f);
		return NULL;
	}

	size_t read = fread(str, sizeof(char), capacity, f);
	fclose(f);

	if (PRINT == true) {
		printf("----\n%s----\n", str);
	}

	return str;
}
