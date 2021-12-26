#pragma once
#include "Entity.h"
/// <summary>
/// Dekorator klasy Entity ma siê zajmowaæ jej sterowaniem.
/// </summary>
class Logics : public Entity { //TODO Narazie napisa³em na sztywno patrol, powinny byæ odzielna klasa abstrackyjna
private:
	/// <summary>
	/// Pole przchowuj¹ce obiekt
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
    /// Kostruktor przekazuj¹cy objekt do sterowania i funkcje nim steruj¹c¹ (nie zaimplementowane)
    /// </summary>
    /// <param name="ent">Obiekt przechowywany</param>
    /// <param name="name">funkcja steruj¹ca</param>
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
	/// Konstruktor przekazzuj¹cy obiektk do sterowania
	/// </summary>
	/// <param name="ent">Obiekt przechowywany</param>
	Logics(Entity* ent);

	/// <summary>
	///  Funkcja przechowuj¹ca zachowanie obiektu
	/// </summary>
	void plan();
	
};