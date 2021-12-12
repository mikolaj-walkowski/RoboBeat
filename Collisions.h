#pragma once
#include <glm//gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SquareCollision;
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

class SquareCollision: public CollisionInterface
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
