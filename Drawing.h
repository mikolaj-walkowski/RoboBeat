#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include <string>
class DrawingInterface
{
public:
	DrawingInterface(glm::vec2* pos);
	virtual void draw(bool flip) = 0;
	glm::vec2* position;
	std::string spName;
};

class DrawSimpleSquare :public DrawingInterface {
public:
	glm::vec4 color;
	float verts[24] = {
		1.0,1.0,0.0,1.0,
		1.0,-1.0,0.0,1.0,
		-1.0,-1.0,0.0,1.0,

		-1.0,1.0,0.0,1.0,
		-1.0,-1.0,0.0,1.0,
		1.0,1.0,0.0,1.0
	};
	glm::mat4 M;
	DrawSimpleSquare(glm::vec2* pos,glm::vec2 _dims, glm::vec4 _color);
	virtual void draw(bool flip = false);
};

class DrawTexturedSquare : public DrawSimpleSquare
{
	std::string texName;
	GLuint currNumber = 0;
	float texCoords[12] ={
		1.0,0.01,
		1.0,0.99,
		0.0,0.99,

		0.0,0.1,
		0.0,.99,
		1.0,0.01
	};
public:
	DrawTexturedSquare(glm::vec2* pos,glm::vec2 _dims, std::string _texName);
	void draw(bool flip);
};

