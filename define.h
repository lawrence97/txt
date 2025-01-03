#pragma once

/* window settings */
#define WIDTH 500
#define HEIGHT 500

/* directory for resources */
#ifndef RES_DIR
#define RES_DIR "./"
#endif

/* shader and texture file names */
#define SHADER "shader.glsl"
#define TEXTURE "font.png"

/* maximum number of character instances in one draw */
#define MAX_CHARACTERS 500

/* debug */
#define PRINT false

/* type -> index of colour in shader */
typedef enum {
	PLAIN = 0,
	SURROUND = 1,
} TYPE;
