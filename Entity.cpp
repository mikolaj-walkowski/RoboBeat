#include "Entity.h"

Entity::Entity(glm::vec2* p, CollisionInterface* cI, PhysicsInterface* pI, DrawingInterface* dI):position(p),collisonInterface(cI),physicsInterface(pI),drawingInterface(dI){
}

Entity::Entity()
{
}

Entity::~Entity()
{
    delete physicsInterface;
    delete collisonInterface;
    delete position;
}

CollisionInterface* Entity::getCollisonInterface() const
{
    return collisonInterface;
}

void Entity::setCollisonInterface(CollisionInterface* collisonInterface)
{
    this->collisonInterface = collisonInterface;
}

PhysicsInterface* Entity::getPhysicsInterface() const
{
    return physicsInterface;
}

void Entity::setPhysicsInterface(PhysicsInterface* physicsInterface)
{
    this->physicsInterface = physicsInterface;
}

glm::vec2* Entity::getPosition() const
{
    return position;
}

void Entity::setPosition(glm::vec2* position)
{
    this->position = position;
}


DrawingInterface* Entity::getDrawingInterface() const
{
    return drawingInterface;
}

void Entity::setDrawingInterface(DrawingInterface* drawingInterface)
{
    this->drawingInterface = drawingInterface;
}

void Entity::draw(const float& dT)
{
    if(physicsInterface != NULL)//TODO napewno zmieniæ
        drawingInterface->draw(physicsInterface->facing);
    else
        drawingInterface->draw(false);
}

void VisitingVisitor::accept(VisitingVisitor*)
{
}

//void VisitingVisitor::reactTo(Player*)
//{
//}

void VisitingVisitor::reactTo(Entity*)
{
}

//Player::Player(glm::vec2* p, CollisionInterface* cI, PhysicsInterface* pI, DrawingInterface* dI):Entity(p,cI,pI,dI)
//{
//}
//
//void Player::logics(const float&)
//{
//}
//
//Object::Object(glm::vec2* p, CollisionInterface* cI, PhysicsInterface* pI, DrawingInterface* dI):Entity(p, cI, pI, dI)
//{
//}
//
//void Object::logics(const float&)
//{
//}
