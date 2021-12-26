#pragma once
#include "Entity.h"
/// <summary>
/// Dekorator klasy Entity ma si� zajmowa� jej sterowaniem.
/// </summary>
class Logics : public Entity { //TODO Narazie napisa�em na sztywno patrol, powinny by� odzielna klasa abstrackyjna
private:
	/// <summary>
	/// Pole przchowuj�ce obiekt
	/// </summary>
	Entity* obj;
	void (*planfunc)();
    void moveLeft();
    void moveRight();
    /// <summary>
    /// Timer dla danego obiektu
    /// </summary>
    float timer = 0; 
public:
    /// <summary>
    /// Kostruktor przekazuj�cy objekt do sterowania i funkcje nim steruj�c� (nie zaimplementowane)
    /// </summary>
    /// <param name="ent">Obiekt przechowywany</param>
    /// <param name="name">funkcja steruj�ca</param>
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
	/// <summary>
	/// Konstruktor przekazzuj�cy obiektk do sterowania
	/// </summary>
	/// <param name="ent">Obiekt przechowywany</param>
	Logics(Entity* ent);

	/// <summary>
	///  Funkcja przechowuj�ca zachowanie obiektu
	/// </summary>
	void plan();
	
};