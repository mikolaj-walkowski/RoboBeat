#include "Physics.h"
#include "constants.h"

void FullDynamicCollsion(glm::vec2 dir,DynamicObject* d1, DynamicObject* d2) {
	auto v1 = dir * glm::dot(d1->velocity, dir);
	auto v2 = -dir * glm::dot(d2->velocity, -dir);

	auto vm1 = dir * glm::dot(d1->momentVelocity, dir);
	auto vm2 = -dir * glm::dot(d2->momentVelocity, -dir);

	d1->velocity += v2*(d2->mass/d1->mass) - v1;
	d2->velocity += v1 * (d1->mass / d2->mass) - v2;
	
	d1->momentVelocity += vm2*(d2->mass/d1->mass) - vm1;
	d2->momentVelocity += vm1 * (d1->mass / d2->mass) - vm2;

	
	*(d1->position) += -dir * safeDist;
	*(d2->position) += dir * safeDist;
}
void StaticDynamicCollision(glm::vec2 dir,StaticObject* s,DynamicObject* d) {
	auto v_along_dir = glm::dot(-dir, d->velocity);
	auto mv_along_dir = glm::dot(-dir, d->momentVelocity);
	
	d->velocity += dir* ((v_along_dir) > 0.f? v_along_dir : 0);
	d->momentVelocity += dir* ((mv_along_dir) > 0.f? mv_along_dir : 0);
	
	*(d->position) += dir * safeDist;
//	printf("vel.x %f, y %f\n", d->velocity.x, d->velocity.y);
}
void FullStaticCollision(glm::vec2 dir,StaticObject* s1, StaticObject* s2) {

}

DynamicObject::DynamicObject(glm::vec2* pos):PhysicsInterface(pos)
{
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
	//printf("Moment velo %f, %f\n", momentVelocity.x, momentVelocity.y);
	*position += velocity * dT + momentVelocity*dT;
	momentVelocity = glm::vec2(0.0, 0.0);
}

StaticObject::StaticObject(glm::vec2* pos):PhysicsInterface(pos)
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

PhysicsInterface::PhysicsInterface(glm::vec2* pos): position(pos)
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
