#ifdef VERTEX
/* -------- Vertex shader -------- */
layout (location = 0) in vec2 vertex;
layout (location = 1) in uint value;
layout (location = 2) in uint type;

vec2 delta = {7.0f, 14.0f};
vec2 screen = {500.0f, 500.0f};
vec2 spacing = {1.0f, 2.0f};
vec2 start = {25.0f, 25.0f};

vec2 normPosition;
vec2 normTranslation;

void main() {

	normPosition.x = (start.x * 2.0f / screen.x) - 1.0f;
	normPosition.y = ((screen.y - start.y) * 2.0f / screen.y) - 1.0f;

	normPosition.x += (vertex.x * delta.x * 2.0f / screen.x);
	normPosition.y += (vertex.y * delta.y * 2.0f / screen.y);

	normTranslation.x = gl_InstanceID * (delta.x + spacing.x) * 2.0f / screen.x;

	normPosition.x += normTranslation.x;
	normPosition.y -= normTranslation.y;

	gl_Position = vec4(normPosition.x, normPosition.y, 1.0f, 1.0f);
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
