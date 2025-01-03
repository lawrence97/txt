#include "handle.h"
#include "keybind.h"
#include "txt.h"

void handleKey(GLFWwindow *window, int key, int scancode, int action, int mods) {

	if (!(action == GLFW_PRESS || action == GLFW_REPEAT)) {
		return;
	}

	Txt *_txt = glfwGetWindowUserPointer(window);
	if (_txt != NULL) {
		if (_txt->handler.mode == EDIT) {
			if (key == GLFW_KEY_ESCAPE) {
				funcNormal(_txt, NULL);
			}
			return;
		}
	}

	for (int i = 0; i < NUM_KEYBINDS; i++) {
		Keybind _keybind = keybinds[i];
		if (key == _keybind.key && mods == _keybind.mods) {
			_keybind.ptr(_txt, &_keybind.key);
			return;
		}
	}

	return;
}

void handleChar(GLFWwindow *window, unsigned int unicode) {

	Txt *_txt = glfwGetWindowUserPointer(window);
	if (_txt != NULL) {
		if (_txt->handler.mode == NORMAL) {
			return;
		}
	}

	funcPrint(_txt, &unicode);

	return;
}
