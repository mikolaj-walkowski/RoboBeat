#version 330

//Uniform variables
uniform mat4 P;
uniform mat4 M;
uniform sampler2D tex;

in vec4 vertex;
in vec2 texCoord;

//Varying variables
out vec2 i_texCoord;


void main(void) {
    gl_Position=P*M*vertex;
    i_texCoord = texCoord;
}
