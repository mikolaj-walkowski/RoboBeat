#pragma once
#include <glm//gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SquareCollision;
/// <summary>
/// Interfejs kolizyjny - zawiera funkcje s�u��ce do wywo�ania odpowiedniej funkcji pomi�dzy dwoma r�nymi 
/// </summary>
class CollisionInterface
{
private:
public:
	glm::vec2* position;
	float range;
	CollisionInterface(glm::vec2* p);
	virtual bool isInRange(CollisionInterface* e)=0;
	virtual glm::vec2 collide(CollisionInterface* c)=0;
	virtual glm::vec2 collideWithSquare(SquareCollision* sq) = 0;
};
/// <summary>
/// Odpowiada za kolzije z innymi obiektami typu prostok�t
/// </summary>
class SquareCollision: public CollisionInterface //TODO zmie� na Rectangle bo square to krind� 
{
public:
	SquareCollision(glm::vec2* pos,glm::vec2 dims);
	//~SquareCollision(); //TODO 
	glm::vec2 dims;

private:
	bool isInRange(CollisionInterface* e);
	glm::vec2 collide(CollisionInterface* c);
	glm::vec2 collideWithSquare(SquareCollision* sq);
};
