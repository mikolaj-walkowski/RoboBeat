#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class DynamicObject;
class StaticObject;
/// <summary>
/// Klasa Abstrakcyjna wymuszaj¹ca zaimplementownie odpowiednich zachowañ przez strategie konkretne.
/// Ka¿da konkretna klasa musi móc przyjmowaæ wszystkie inne klasy konkretne jako wizytorów a tak¿e samma je odwiedzaæ.
/// </summary>
class PhysicsInterface
{
public:
	PhysicsInterface(glm::vec2* pos,glm::vec2 dims);

	/// <summary>
	/// Funkcja przyjmuj¹ca wizytora w odwiedzanym
	/// </summary>
	/// <param name="dir">Kierunek kolizji od pierwszego obiektu w parze do drugiego</param>
	/// <param name="p">Obiekt odwiedzaj¹cy</param>
	virtual void resolveCollision(glm::vec2 dir,PhysicsInterface* p)=0;
	/// <summary>
	/// Funkcja odpowiadaj¹ca w wizytorze na kolizje ze statycznym obiektem
	/// </summary>
	/// <param name="dir">Kierunek kolizji od pierwszego obiektu w parze do drugiego</param>
	/// <param name="s">Obiekt odwiedzany</param>
	virtual void resolveCollisionWith(glm::vec2 dir,StaticObject* s)=0;
	/// <summary>
	/// Funkcja odpowiadaj¹ca w wizytorze na kolizje z dynamicznym obiektem
	/// </summary>
	/// <param name="dir">Kierunek kolizji od pierwszego obiektu w parze do drugiego</param>
	/// <param name="s">Obiekt odwiedzany</param>
	virtual void resolveCollisionWith(glm::vec2 dir,DynamicObject* d)=0;
	/// <summary>
	/// Funkcja zmienia prêdkoœæ obiektu w odpowiedzi na sta³e si³y.
	/// </summary>
	/// <param name="dT"> czas pomiêdzy klatkami</param>
	virtual void changeVelo(const float& dT); //TODO nie lubie tego systemu
	/// <summary>
	/// Funkcja przesuwa obiekt zgodnie z jego prêdkoœci¹.
	/// </summary>
	/// <param name="dT"><czas pomiêdzy klatkami/param>
	virtual void move(const float& dT);
	/// <summary>
	/// Funkcja ustawia prêdkoœæ steruj¹c¹ 
	/// </summary>
	/// <param name=""></param>
	virtual void setMomentVelocity(glm::vec2); //TODO mo¿e coœ mniej brzydkiego moze przenieœæ do logiki 
	bool facing = false; //false = prawo
	glm::vec2* position;
	/// <summary>
	/// Szerokoœæi wysokoœæ
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
