#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class DynamicObject;
class StaticObject;
class PhysicsInterface
{
public:
	PhysicsInterface(glm::vec2* pos,glm::vec2 dims);
	virtual void resolveCollision(glm::vec2 dir,PhysicsInterface* p)=0;
	virtual void resolveCollisionWith(glm::vec2 dir,StaticObject* s)=0;
	virtual void resolveCollisionWith(glm::vec2 dir,DynamicObject* d)=0;
	virtual void changeVelo(const float& dT); //TODO nie lubie tego systemu
	virtual void move(const float& dT);
	virtual void setMomentVelocity(glm::vec2); //TODO mo¿e coœ mniej brzydkiego
	bool facing = false; //false = prawo
	glm::vec2* position;
	glm::vec2 dimentions;
	float g = 9.98*50;
	bool touching_stat = false;
	};

class DynamicObject : public PhysicsInterface {
public:
	DynamicObject(glm::vec2*,glm::vec2);
	glm::vec2 velocity;
	float speed = 200;
	glm::vec2 momentVelocity; //TODO nie lubie tego jeszcze bardziej 
	float mass;
	virtual void resolveCollision(glm::vec2 dir,PhysicsInterface* p);
	virtual void resolveCollisionWith(glm::vec2 dir,StaticObject* s);
	virtual void resolveCollisionWith(glm::vec2 dir,DynamicObject* d);
	void setMomentVelocity(glm::vec2);
	virtual void changeVelo(const float& dT);
	virtual void move(const float& dT);
};

class StaticObject : public PhysicsInterface {
public:
	StaticObject(glm::vec2*, glm::vec2);
	virtual void resolveCollision(glm::vec2 dir,PhysicsInterface* p);
	virtual void resolveCollisionWith(glm::vec2 dir,StaticObject* s);
	virtual void resolveCollisionWith(glm::vec2 dir,DynamicObject* d);
};
