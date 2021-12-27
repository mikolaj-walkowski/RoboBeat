#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include <string>
/// <summary>
/// Klasa definiuj¹ca strategiê rysowania  
/// </summary>
class DrawingInterface
// TODO warto by by³o zmieniæ na prawdziwy wzorzec stratega,tóry bêdzie mo¿na wymieniaæ bez inicjalizowania tablicy verts i texCoords

{
public:
	DrawingInterface(glm::vec2* pos);
	/// <summary>
	/// Funkcja rysuj¹ca
	/// </summary>
	/// <param name="flip"> Czy textura powinna zostaæ obrócona wokó³ oY</param>
	virtual void draw(bool flip) = 0;
	glm::vec2* position;
	/// <summary>
	/// Nazwa programu cieniuj¹cego
	/// </summary>
	std::string spName;
};
/// <summary>
/// Rysuje prostok¹t o danej wysokoœci i szerokoœci wype³niony danym kolorem
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
/// Rysuje prostok¹t o danej wysokoœci i szerokoœci i koloruje za pomoc¹ tekstury
/// </summary>
class DrawTexturedSquare : public DrawSimpleSquare
{
	std::string texName;
	GLuint currNumber = 0;
	float texCoords[12] ={// nie wiem dlaczego musze odejmowaæ i dodawaæ to 0.01
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

