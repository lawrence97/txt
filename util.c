#include "util.h"

GLFWwindow *newWindow(int width, int height, char *title) {

	if (glfwInit() == 0) {
		return NULL;
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow *_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (_window == NULL) {
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(_window);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
		glfwTerminate();
		return NULL;
	}

	return _window;
}

void destroyWindow(GLFWwindow *window) {

	glfwDestroyWindow(window);
	glfwTerminate();

	return;
}
