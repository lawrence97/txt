#include "batch.h"
#include "defines.h"

static Character chars[MAX_CHARACTERS];

Batch newBatch(size_t capacity, GLuint shader) {

	Batch bat = {0};

	glGenVertexArrays(1, &bat.vao);
	glGenBuffers(1, &bat.vbo);
	glGenBuffers(1, &bat.bbo);

	glBindVertexArray(bat.vao);

	GLuint attribVertex = glGetAttribLocation(shader, "vertex");
	GLuint attribValue = glGetAttribLocation(shader, "value");
	GLuint attribType = glGetAttribLocation(shader, "type");
	GLuint attribLine = glGetAttribLocation(shader, "line");
	GLuint attribTab = glGetAttribLocation(shader, "tab");
	GLuint attribOffset = glGetAttribLocation(shader, "offset");

	Vector vertices[6] = {
		{.x = .0f, .y = .0f},	 {.x = 1.0f, .y = .0f},	 {.x = 1.0f, .y = -1.0f},
		{.x = 1.0f, .y = -1.0f}, {.x = .0f, .y = -1.0f}, {.x = .0f, .y = .0f},
	};

	glBindBuffer(GL_ARRAY_BUFFER, bat.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(attribVertex, 2, GL_FLOAT, GL_FALSE, sizeof(Vector), (void *)0);
	glEnableVertexAttribArray(attribVertex);
	glVertexAttribDivisor(attribVertex, 0);

	glBindBuffer(GL_ARRAY_BUFFER, bat.bbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Character) * capacity, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribIPointer(attribValue, 1, GL_INT, sizeof(Character), (void *)(sizeof(int) * 0));
	glEnableVertexAttribArray(attribValue);
	glVertexAttribDivisor(attribValue, 1);

	glVertexAttribIPointer(attribType, 1, GL_INT, sizeof(Character), (void *)(sizeof(int) * 1));
	glEnableVertexAttribArray(attribType);
	glVertexAttribDivisor(attribType, 1);

	glVertexAttribIPointer(attribLine, 1, GL_INT, sizeof(Character), (void *)(sizeof(int) * 2));
	glEnableVertexAttribArray(attribLine);
	glVertexAttribDivisor(attribLine, 1);

	glVertexAttribIPointer(attribTab, 1, GL_INT, sizeof(Character), (void *)(sizeof(int) * 3));
	glEnableVertexAttribArray(attribTab);
	glVertexAttribDivisor(attribTab, 1);

	glVertexAttribIPointer(attribOffset, 1, GL_INT, sizeof(Character), (void *)(sizeof(int) * 4));
	glEnableVertexAttribArray(attribOffset);
	glVertexAttribDivisor(attribOffset, 1);

	return bat;
}

Character stringBatch(Batch *batch, char *string, size_t size, Character trace) {

	if (size > MAX_CHARACTERS) {
		size = MAX_CHARACTERS;
	}

	int type = trace.type;
	int line = trace.line;
	int tab = trace.tab;
	int offset = trace.offset;

	Character c = {0};

	for (int i = 0; i < size; i++) {

		/* --- pre character checks */

		c.value = string[i];
		c.line = line;
		c.tab = tab;
		c.offset = offset;

		if (c.value == ']' || c.value == ')' || c.value == '}') {
			type = PLAIN;
		}
		c.type = type;

		/* --- set character */

		chars[batch->size + i] = c;

		/* --- post character checks */

		if (c.value == '[' || c.value == '(' || c.value == '{') {
			type = SURROUND;
		}

		if (c.value == '\n') {
			line++;
			offset += i + 1;
			tab = trace.tab;
		} else if (c.value == '\t') {
			tab++;
		}
	}

	batch->size += size;

	return c;
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
