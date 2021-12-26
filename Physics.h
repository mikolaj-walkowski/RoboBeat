#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class DynamicObject;
class StaticObject;
/// <summary>
/// Klasa Abstrakcyjna wymuszaj�ca zaimplementownie odpowiednich zachowa� przez strategie konkretne.
/// Ka�da konkretna klasa musi m�c przyjmowa� wszystkie inne klasy konkretne jako wizytor�w a tak�e samma je odwiedza�.
/// </summary>
class PhysicsInterface
{
public:
	PhysicsInterface(glm::vec2* pos,glm::vec2 dims);

	/// <summary>
	/// Funkcja przyjmuj�ca wizytora w odwiedzanym
	/// </summary>
	/// <param name="dir">Kierunek kolizji od pierwszego obiektu w parze do drugiego</param>
	/// <param name="p">Obiekt odwiedzaj�cy</param>
	virtual void resolveCollision(glm::vec2 dir,PhysicsInterface* p)=0;
	/// <summary>
	/// Funkcja odpowiadaj�ca w wizytorze na kolizje ze statycznym obiektem
	/// </summary>
	/// <param name="dir">Kierunek kolizji od pierwszego obiektu w parze do drugiego</param>
	/// <param name="s">Obiekt odwiedzany</param>
	virtual void resolveCollisionWith(glm::vec2 dir,StaticObject* s)=0;
	/// <summary>
	/// Funkcja odpowiadaj�ca w wizytorze na kolizje z dynamicznym obiektem
	/// </summary>
	/// <param name="dir">Kierunek kolizji od pierwszego obiektu w parze do drugiego</param>
	/// <param name="s">Obiekt odwiedzany</param>
	virtual void resolveCollisionWith(glm::vec2 dir,DynamicObject* d)=0;
	/// <summary>
	/// Funkcja zmienia pr�dko�� obiektu w odpowiedzi na sta�e si�y.
	/// </summary>
	/// <param name="dT"> czas pomi�dzy klatkami</param>
	virtual void changeVelo(const float& dT); //TODO nie lubie tego systemu
	/// <summary>
	/// Funkcja przesuwa obiekt zgodnie z jego pr�dko�ci�.
	/// </summary>
	/// <param name="dT"><czas pomi�dzy klatkami/param>
	virtual void move(const float& dT);
	/// <summary>
	/// Funkcja ustawia pr�dko�� steruj�c� 
	/// </summary>
	/// <param name=""></param>
	virtual void setMomentVelocity(glm::vec2); //TODO mo�e co� mniej brzydkiego moze przenie�� do logiki 
	bool facing = false; //false = prawo
	glm::vec2* position;
	/// <summary>
	/// Szeroko��i wysoko��
	/// </summary>
	glm::vec2 dimentions;
	float g = 9.98*50;
	/// <summary>
	/// Czy obiekt ma ziemie pod nogami? xd
	/// </summary>
	bool touching_stat = false;
	};
/// <summary>
/// Strategia zachowania dla obiektu ruchomego
/// </summary>
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
/// <summary>
/// Strategia zachowania dla obiektu statycznego
/// </summary>
class StaticObject : public PhysicsInterface {
public:
	StaticObject(glm::vec2*, glm::vec2);
	virtual void resolveCollision(glm::vec2 dir,PhysicsInterface* p);
	virtual void resolveCollisionWith(glm::vec2 dir,StaticObject* s);
	virtual void resolveCollisionWith(glm::vec2 dir,DynamicObject* d);
};
