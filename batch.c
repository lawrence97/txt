#include "batch.h"
#include "defines.h"

static Character chars[MAX_CHARACTERS];

Batch newBatch(size_t capacity) {

	Batch bat = {0};

	glGenVertexArrays(1, &bat.vao);
	glGenBuffers(1, &bat.vbo);
	glGenBuffers(1, &bat.bbo);

	glBindVertexArray(bat.vao);

	Vector vertices[6] = {
		{.x = .0f, .y = .0f},	 {.x = 1.0f, .y = .0f},	 {.x = 1.0f, .y = -1.0f},
		{.x = 1.0f, .y = -1.0f}, {.x = .0f, .y = -1.0f}, {.x = .0f, .y = .0f},
	};

	glBindBuffer(GL_ARRAY_BUFFER, bat.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribDivisor(0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, bat.bbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Batch) * capacity, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, sizeof(Batch), (void *)(sizeof(unsigned int) * 0));
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	glVertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, sizeof(Batch), (void *)(sizeof(unsigned int) * 1));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	return bat;
}

void newString(Batch *batch, char *string, size_t size) {

	Character c = {0};

	if (size > MAX_CHARACTERS) {
		size = MAX_CHARACTERS;
	}

	for (int i = 0; i < size; i++) {
		c.value = string[i];
		c.type = 0;
		chars[i] = c;
	}

	batch->size += size;

	return;
}

void updateBatch(Batch *batch) {

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Character) * batch->size, chars);

	return;
}

void drawBatch(size_t size) {

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, size);

	return;
}

void clearBatch(Batch *batch) {

	batch->size = 0;

	return;
}

void destroyBatch(Batch batch) {

	glDeleteVertexArrays(1, &batch.vao);
	glDeleteBuffers(1, &batch.vbo);
	glDeleteBuffers(1, &batch.bbo);

	return;
}
