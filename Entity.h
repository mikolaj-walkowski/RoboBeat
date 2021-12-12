#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Collisions.h"
#include "Physics.h"
//#include "Logic.h"
#include "Drawing.h"
class Player;
class Entity;

class VisitingVisitor {
public:
    virtual void accept(VisitingVisitor*);
    virtual void reactTo(Player*);
    virtual void reactTo(Entity*);

};
class Entity : public VisitingVisitor
{
public:
private:
	CollisionInterface* collisonInterface;
	PhysicsInterface* physicsInterface;
    DrawingInterface* drawingInterface;
	glm::vec2* position;
public:
    
    Entity(glm::vec2* p, CollisionInterface* cI, PhysicsInterface* pI, DrawingInterface* dI);
	~Entity();

    CollisionInterface* getCollisonInterface() const;
    void setCollisonInterface(CollisionInterface* collisonInterface);

    PhysicsInterface* getPhysicsInterface() const;
    void setPhysicsInterface(PhysicsInterface* physicsInterface);

    glm::vec2* getPosition() const;
    void setPosition(glm::vec2* position);

public:
    DrawingInterface* getDrawingInterface() const;
    void setDrawingInterface(DrawingInterface* drawingInterface);

};

class Player : public Entity
{
public:
	//Player();
	//~Player();

private:

};
