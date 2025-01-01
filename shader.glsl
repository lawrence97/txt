#ifdef VERTEX
/* -------- Vertex shader -------- */

attribute vec2 vertex;
attribute int value;
attribute int type;
attribute int line;
attribute int tab;
attribute int offset;

int tabSize= 4;
vec2 delta = {7.0f, 14.0f};
vec2 screen = {500.0f, 500.0f};
vec2 spacing = {1.0f, 2.0f};
vec2 padding = {25.0f, 25.0f};

vec2 normPosition;
vec2 normTranslation;

flat out int _value;
flat out int _type;
out vec2 _vertex;

void main() {

	_value = value;
	_type = type;
	_vertex = vertex;

	normPosition.x = (padding.x * (2.0f / screen.x)) - 1.0f;
	normPosition.y = ((screen.y - padding.y) * (2.0f / screen.y)) - 1.0f;

	normPosition.x += vertex.x * delta.x * (2.0f / screen.x);
	normPosition.y += vertex.y * delta.y * (2.0f / screen.y);

	normTranslation.x = (gl_InstanceID - offset + ((tabSize- 1) * tab)) * (delta.x + spacing.x) * (2.0f / screen.x);
	normTranslation.y = line * (delta.y + spacing.y) * (2.0f / screen.y);

	normPosition.x += normTranslation.x;
	normPosition.y -= normTranslation.y;

	gl_Position = vec4(normPosition.x, normPosition.y, 1.0f, 1.0f);
}

/* ------------------------------- */
#endif


#ifdef FRAGMENT
/* -------- Fragment shader -------- */

struct Colour {
	vec4 foreground;
	vec4 background;
};

uniform sampler2D tex;

flat in int _value;
flat in int _type;
in vec2 _vertex;

int divisor = 18;
ivec2 deltaTex = {7, 14};
ivec2 screenTex = {128, 128};
ivec2 paddingTex = {1, 1};

Colour colours[2] = {
	{{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, .0f}}, // 0
	{{.6f, .5f, .8f, 1.0f}, {1.0f, 1.0f, 1.0f, .1f}}, // 1
};

ivec2 texel;

out vec4 fragColour;

void main() {

	texel = ivec2(paddingTex.x + (_vertex.x * deltaTex.x), screenTex.y - paddingTex.y + (_vertex.y * deltaTex.y));

	texel.x += deltaTex.x * int(mod(_value - 1, divisor));
	texel.y -= deltaTex.y * int((_value - mod(_value - 1, divisor)) / divisor);

	fragColour = (colours[_type].foreground * texelFetch(tex, texel, 0)) + (colours[_type].background * (vec4(1.0f) -  texelFetch(tex, texel, 0)));
}

/* --------------------------------- */
#endif
