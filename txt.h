#pragma once

#include "util.h"

typedef struct {
	GLFWwindow *window;
} Txt;

int initialiseTxt(Txt *txt);
void runTxt(Txt *txt);
void shutdownTxt(Txt *txt);
