#ifdef VERTEX
/* -------- Vertex shader -------- */

void main() {
	gl_Position = vec4(.5f, .5f, 1.0f, 1.0f);
}

/* ------------------------------- */
#endif


#ifdef FRAGMENT
/* -------- Fragment shader -------- */

uniform sampler2D tex;

out vec4 colour;

void main() {
	colour = vec4(1.0f);
}

/* --------------------------------- */
#endif
