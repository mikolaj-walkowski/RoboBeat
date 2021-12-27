#include "Physics.h"
#include "constants.h"

void FullDynamicCollsion(glm::vec2 dir,DynamicObject* d1, DynamicObject* d2) { //TODO kolizja od góry jest tak mocno se.
	auto vd1 = glm::dot(d1->velocity, dir);
	auto vd2 = glm::dot(d2->velocity, -dir);

	auto vmd1 = glm::dot(d1->momentVelocity, dir);
	auto vmd2 = glm::dot(d2->momentVelocity, -dir);

	if (vmd1 + vd1 >= 0 && vmd2 + vd2 >= 0)
		return;

	auto v1 = dir * vd1;
	auto v2 = -dir * vd2;

	auto vm1 = dir * vmd1;
	auto vm2 = -dir * vmd2;

	printf("Vmp % f, v2 % f\n", vm1.x,vm2.x);

	auto vk = (v1 * d1->mass + v2 * d2->mass) / (d1->mass + d2->mass);
	auto vmk = (vm1 * d1->mass + vm2 * d2->mass) / (d1->mass + d2->mass);

	d1->velocity += vk - v1;
	d2->velocity += vk - v2;
	
	d1->momentVelocity += vmk -vm1;
	d2->momentVelocity += vmk -vm2;

	printf("Vmk % f, v2 % f\n", d1->momentVelocity.x, d2->momentVelocity.x);
	
	auto avg_pos = (*(d1->position) + *(d2->position)) / 2.f;
	if (dir.x != 0) {
		(d1->position)->x = avg_pos.x + dir.x * ((d1->dimentions.x / 2.f + d2->dimentions.x / 2.f)/2.f);
		(d2->position)->x = avg_pos.x - dir.x * ((d1->dimentions.x / 2.f + d2->dimentions.x / 2.f)/2.f);

	}
	if (dir.y != 0) {
		(d1->position)->y = avg_pos.y + dir.y * ((d1->dimentions.y / 2.f + d2->dimentions.y / 2.f)/2.f + safeDist);
		(d1->position)->y = avg_pos.y - dir.y * ((d1->dimentions.y / 2.f + d2->dimentions.y / 2.f)/2.f + safeDist);
	}
}
void StaticDynamicCollision(glm::vec2 dir,StaticObject* s,DynamicObject* d) {
	auto v_along_dir = glm::dot(-dir, d->velocity);
	auto mv_along_dir = glm::dot(-dir, d->momentVelocity);
	
	d->velocity += dir* ((v_along_dir) > 0.f? v_along_dir : 0);
	d->momentVelocity += dir* ((mv_along_dir) > 0.f? mv_along_dir : 0);
	
	if (dir.x != 0) {
		(d->position)->x = (s->position)->x + dir.x * (s->dimentions.x/2 + d->dimentions.x/2);
	}
	if (dir.y != 0) {
		(d->position)->y = (s->position)->y + dir.y * (s->dimentions.y/2 + d->dimentions.y/2);
	}

	//	printf("vel.x %f, y %f\n", d->velocity.x, d->velocity.y);
}
void FullStaticCollision(glm::vec2 dir,StaticObject* s1, StaticObject* s2) {

}

DynamicObject::DynamicObject(glm::vec2* pos, glm::vec2 dims):PhysicsInterface(pos, dims)
{
	velocity = glm::vec2(0.f, 0.f);
	momentVelocity = glm::vec2(0.f, 0.0f);
	mass = 10;
}

void DynamicObject::resolveCollision(glm::vec2 dir,PhysicsInterface* p)
{
	p->resolveCollisionWith(dir,this);
}

void DynamicObject::resolveCollisionWith(glm::vec2 dir,StaticObject* s)
{
	StaticDynamicCollision(-dir,s, this);
}

void DynamicObject::resolveCollisionWith(glm::vec2 dir,DynamicObject* d)
{
	FullDynamicCollsion(-dir, d, this);
}

void DynamicObject::setMomentVelocity(glm::vec2 _mV)
{
//	printf("Moment velo %d, %d\n", momentVelocity.x, momentVelocity.y);
	momentVelocity = _mV * speed;
}

void DynamicObject::changeVelo(const float& dT)
{
	velocity +=  glm::vec2(0.0,-(g)*dT);
}

void DynamicObject::move(const float& dT)
{
	if (momentVelocity.x > 0) {
		facing = false;
	}
	else if (momentVelocity.x < 0) {
		facing = true;
	}
	if (touching_stat) {
		velocity.x -= velocity.x *0.3*dT;
	}
	*position += velocity * dT + momentVelocity*dT;
	momentVelocity = glm::vec2(0.0, 0.0);
	
//	printf("Pos % f, % f\n", position->x,position->y);

//	printf("Vel % f, % f\n", velocity.x,velocity.y);

}

StaticObject::StaticObject(glm::vec2* pos, glm::vec2 dims):PhysicsInterface(pos, dims)
{
}

void StaticObject::resolveCollision(glm::vec2 dir,PhysicsInterface* p)
{
	p->resolveCollisionWith(dir,this);
}

void StaticObject::resolveCollisionWith(glm::vec2 dir,StaticObject* s)
{
	FullStaticCollision(dir,s,this);
}

void StaticObject::resolveCollisionWith(glm::vec2 dir,DynamicObject* d)
{

	StaticDynamicCollision(-dir,this,d);
}

PhysicsInterface::PhysicsInterface(glm::vec2* pos, glm::vec2 dims): position(pos), dimentions(dims)
{

}

void PhysicsInterface::changeVelo(const float& dT)
{

}

void PhysicsInterface::move(const float& dT)
{
}

void PhysicsInterface::setMomentVelocity(glm::vec2)
{
}
