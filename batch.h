#pragma once

#include <glad/glad.h>

typedef struct {
	float x;
	float y;
} Vector;

typedef struct {
	int value;
	int type;
	int line;
	int tab;
	int offset;
} Character;

typedef struct {
	GLuint vao;
	GLuint vbo;
	GLuint bbo;
	size_t size;
} Batch;

Batch newBatch(size_t capacity, GLuint shader);
void stringBatch(Batch *batch, char *string, size_t size);
void updateBatch(Batch *batch);
void drawBatch(size_t size);
void clearBatch(Batch *batch);
void destroyBatch(Batch batch);
