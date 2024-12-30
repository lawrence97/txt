#pragma once

#include "util.h"
#include "batch.h"

typedef struct {
	GLFWwindow *window;
	GLuint shader;
	GLuint texture;
	Batch batch;
} Txt;

int initialiseTxt(Txt *txt);
void runTxt(Txt *txt);
void shutdownTxt(Txt *txt);
