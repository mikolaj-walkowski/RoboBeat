#version 330

//Uniform variables
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec4 vertex;

//Varying variables
out vec4 i_color;

void main(void) {
    gl_Position=P*V*M*vertex;
}
