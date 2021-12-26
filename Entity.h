#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Collisions.h"
#include "Physics.h"
//#include "Logic.h"
#include "Drawing.h"
class Player;
class Entity;
/// <summary>
/// Wizytor obiektu Entity mo�e si�  przyda� w przysz�o�ci
/// </summary>
class VisitingVisitor {
public:
    virtual void accept(VisitingVisitor*);
    /*virtual void reactTo(Player*);*/
    virtual void reactTo(Entity*);

};

/// <summary>
/// G��wna klasa silnika reprezentuje dowolny obiekt w grze i jego podstawowe zachowania w �wiecie gry.
/// </summary>
class Entity : public VisitingVisitor
{
public:
private:
	CollisionInterface* collisonInterface;
	PhysicsInterface* physicsInterface;
    DrawingInterface* drawingInterface;
	glm::vec2* position;
public:
    /// <summary>
    /// Konstruktor two��cy obiekt z wymienneymi strategiami
    /// </summary>
    /// <param name="p">Pozycja obiektu dzielona mi�dzy wieloma sk�adowymi Entity</param>
    /// <param name="cI">Strategia Kolizyjna</param>
    /// <param name="pI">Strategia Fizyczna</param>
    /// <param name="dI">Strategia rysowania</param>
    Entity(glm::vec2* p, CollisionInterface* cI, PhysicsInterface* pI, DrawingInterface* dI);
    Entity();
	~Entity();

    virtual CollisionInterface* getCollisonInterface() const;
    virtual void setCollisonInterface(CollisionInterface* collisonInterface);

    virtual PhysicsInterface* getPhysicsInterface() const;
    virtual void setPhysicsInterface(PhysicsInterface* physicsInterface);

    virtual glm::vec2* getPosition() const;
    virtual void setPosition(glm::vec2* position);

    virtual DrawingInterface* getDrawingInterface() const;
    virtual void setDrawingInterface(DrawingInterface* drawingInterface);
    /// <summary>
    ///  Funkcja opakowuje funkcje draw() ze sterategi DrawingInterface i jest defacto kontrolerem animacji
    /// </summary>
    virtual void draw(const float& dT);
   // virtual void logics(const  float &dT) = 0;
};
//class Object : public Entity {
//public:
//    Object(glm::vec2* p, CollisionInterface* cI, PhysicsInterface* pI, DrawingInterface* dI);
//    void logics(const float&);
//};
//
//class Player : public Entity {
//public:
//    Player(glm::vec2* p, CollisionInterface* cI, PhysicsInterface* pI, DrawingInterface* dI);
//    void logics(const float&);
//private:
//
//};
