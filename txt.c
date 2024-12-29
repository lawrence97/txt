#include "txt.h"

#define WIDTH 500
#define HEIGHT 500

int initialiseTxt(Txt *txt) {

	txt->window = newWindow(WIDTH, HEIGHT, "txt");
	if (txt->window == NULL) {
		return -1;
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

	destroyWindow(txt->window);
	txt->window = NULL;

	return;
}
