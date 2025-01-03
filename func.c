#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "func.h"

void funcQuit(Txt *txt, void *opt) {

	glfwSetWindowShouldClose(txt->window, 1);

	return;
}

void funcNormal(Txt *txt, void *opt) {

	txt->handler.mode = NORMAL;

	return;
}

void funcEdit(Txt *txt, void *opt) {

	txt->handler.mode = EDIT;

	return;
}

void funcPrint(Txt *txt, void *opt) {

	printf("func:Print (key=[%s])\n", (char *)opt);

	return;
}
