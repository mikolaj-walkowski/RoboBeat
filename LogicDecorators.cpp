#include "LogicDecorators.h"
#include "Pipeline.h"

Logics::Logics(Entity* ent):obj(ent)
{
    
}

void Logics::plan()
{
    timer = (timer < 2.f) ? timer + Pipeline::getInstance()->dT : 0.f;
    if (timer < 1.f)
        moveLeft();
    else
        moveRight();
}

void Logics::moveLeft()
{
    getPhysicsInterface()->setMomentVelocity(glm::vec2(-1.f, 0.f));
}

void Logics::moveRight()
{
    getPhysicsInterface()->setMomentVelocity(glm::vec2(1.f, 0.f));
}

Logics::Logics(Entity* ent, void(*name)()):obj(ent),planfunc(name)
{
}

Logics::~Logics()
{
    delete obj;
}

CollisionInterface* Logics::getCollisonInterface() const
{
    return obj->getCollisonInterface();
}

void Logics::setCollisonInterface(CollisionInterface* collisonInterface)
{
    obj->setCollisonInterface(collisonInterface);
}

PhysicsInterface* Logics::getPhysicsInterface() const
{
    return obj->getPhysicsInterface();
}

void Logics::setPhysicsInterface(PhysicsInterface* physicsInterface)
{
    obj->setPhysicsInterface(physicsInterface);
}

glm::vec2* Logics::getPosition() const
{
    return obj->getPosition();
}

void Logics::setPosition(glm::vec2* position)
{
    obj->setPosition(position);
}


DrawingInterface* Logics::getDrawingInterface() const
{
    return obj->getDrawingInterface();
}

void Logics::setDrawingInterface(DrawingInterface* drawingInterface)
{
    obj->setDrawingInterface(drawingInterface);
}

void Logics::draw(const float& dT)
{
    obj->getDrawingInterface()->draw(obj->getPhysicsInterface()->facing);
}

