#version 330

uniform sampler2D tex;

in vec2 i_texCoord;

out vec4 pixelColor;

void main(void) {
	pixelColor = texture(tex,vec2(0.4,1));// texture(tex, i_texCoord);
}
