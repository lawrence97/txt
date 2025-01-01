#include <string.h>

#include "batch.h"
#include "defines.h"
#include "txt.h"
#include "util.h"

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

	txt->batch = newBatch(MAX_CHARACTERS, txt->shader);

	return 0;
}

void runTxt(Txt *txt) {

	GLFWwindow *_window = txt->window;
	Batch _batch = txt->batch;

	glClearColor(.2f, .2f, .3f, 1.0f);
	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Character trace;
	char *str = "long\ttab\na[text]b. New sentence.";
	trace = stringBatch(&_batch, str, 18, (Character){0});
	trace = stringBatch(&_batch, &str[18], strlen(str) - 18, trace);
	char *info = "filename.ext";
	trace = stringBatch(&_batch, info, strlen(info), (Character){.line = 28, .tab = 5, 0});
	updateBatch(&_batch);

	while (!glfwWindowShouldClose(_window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		drawBatch(_batch.size);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	return;
}

void shutdownTxt(Txt *txt) {

	destroyBatch(txt->batch);
	txt->batch = (Batch){0};

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
