#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include <string>
/// <summary>
/// Klasa definiuj�ca strategi� rysowania  
/// </summary>
class DrawingInterface
// TODO warto by by�o zmieni� na prawdziwy wzorzec stratega,t�ry b�dzie mo�na wymienia� bez inicjalizowania tablicy verts i texCoords

{
public:
	DrawingInterface(glm::vec2* pos);
	/// <summary>
	/// Funkcja rysuj�ca
	/// </summary>
	/// <param name="flip"> Czy textura powinna zosta� obr�cona wok� oY</param>
	virtual void draw(bool flip) = 0;
	glm::vec2* position;
	/// <summary>
	/// Nazwa programu cieniuj�cego
	/// </summary>
	std::string spName;
};
/// <summary>
/// Rysuje prostok�t o danej wysoko�ci i szeroko�ci wype�niony danym kolorem
/// </summary>
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
/// <summary>
/// Rysuje prostok�t o danej wysoko�ci i szeroko�ci i koloruje za pomoc� tekstury
/// </summary>
class DrawTexturedSquare : public DrawSimpleSquare
{
	std::string texName;
	GLuint currNumber = 0;
	float texCoords[12] ={// nie wiem dlaczego musze odejmowa� i dodawa� to 0.01
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

