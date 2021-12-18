#version 330

//Uniform variables
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform sampler2D tex;
uniform int flip;
in vec4 vertex;
in vec2 texCoord;

//Varying variables
out vec2 i_texCoord;


void main(void) {
    gl_Position=P*V*M*vertex;
    if(flip == 1)
    {
        i_texCoord = vec2(1.0 - texCoord.x,texCoord.y);
    }
    else{
    i_texCoord = texCoord;
    }
}
