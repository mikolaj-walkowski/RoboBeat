#pragma once
#include "Entity.h"

class Logics : public Entity { //TODO Narazie napisa³em na sztywno patrol, powinny byæ odzielna klasa abstrackyjna
private:
	Entity* obj;
	void (*planfunc)();
    void moveLeft();
    void moveRight();
    float timer = 0; 
public:
    Logics(Entity* ent, void(*name)());
    ~Logics();

    CollisionInterface* getCollisonInterface() const;
    void setCollisonInterface(CollisionInterface* collisonInterface);

    PhysicsInterface* getPhysicsInterface() const;
    void setPhysicsInterface(PhysicsInterface* physicsInterface);

    glm::vec2* getPosition() const;
    void setPosition(glm::vec2* position);

    DrawingInterface* getDrawingInterface() const;
    void setDrawingInterface(DrawingInterface* drawingInterface);

    void draw(const float& dT);

	Logics(Entity* ent);
	void plan();
	
};