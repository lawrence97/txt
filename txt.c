#include "txt.h"
#include "util.h"

#define WIDTH 500
#define HEIGHT 500

#ifndef RES_DIR
#define RES_DIR "./"
#endif

#define SHADER "shader.glsl"
#define TEXTURE "font.png"

int initialiseTxt(Txt *txt) {

	txt->window = newWindow(WIDTH, HEIGHT, "txt");
	if (txt->window == NULL) {
		return -1;
	}

	txt->shader = newShader(RES_DIR SHADER);
	if (txt->shader == 0) {
		shutdownTxt(txt);
		return -2;
	}

	txt->texture = newTexture(RES_DIR TEXTURE);
	if (txt->texture == 0) {
		shutdownTxt(txt);
		return -3;
	}

	return 0;
}

void runTxt(Txt *txt) {

	GLFWwindow *_window = txt->window;

	glClearColor(.2f, .2f, .3f, 1.0f);
	glViewport(0, 0, WIDTH, HEIGHT);

	while (!glfwWindowShouldClose(_window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	return;
}

void shutdownTxt(Txt *txt) {

	if (txt->texture != 0) {
		destroyTexture(txt->texture);
		txt->texture = 0;
	}

	if (txt->shader != 0) {
		destroyShader(txt->shader);
		txt->shader = 0;
	}

	if (txt->window != NULL) {
		destroyWindow(txt->window);
		txt->window = NULL;
	}

	return;
}
