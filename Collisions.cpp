#include "Collisions.h"
template<typename T>
bool inRange(const T& x, const T& b, const T& e) {
	if (b <= x && x <= e) return true;
	else return false;
}
//Zwraca wektor z 1 obiektu do 2 
glm::vec2 collisionSquareSquare(SquareCollision* o1, SquareCollision* o2) {
	auto x11 = o1->position->x - o1->dims.x / 2, x12 = o1->position->x + o1->dims.x / 2, y11 = o1->position->y - o1->dims.y / 2, y12 = o1->position->y + o1->dims.y / 2, x1 = o1->position->x, y1 = o1->position->y;
	auto x21 = o2->position->x - o2->dims.x / 2, x22 = o2->position->x + o2->dims.x / 2, y21 = o2->position->y - o2->dims.y / 2, y22 = o2->position->y + o2->dims.y / 2, x2 = o1->position->x, y2 = o2->position->y;

	if ((inRange(x21, x11, x12) || inRange(x11, x21, x22)) && (inRange(y21, y11, y12) || inRange(y11, y21, y22))) {
	//	printf("Collison Deteccted a(%f, %f, %f, %f), b(%f, %f, %f, %f)\n", x11, x12, y11, y12, x21, x22, y21, y22);
		auto b_dist = glm::abs(y11 - y22), t_dist = glm::abs(y12 - y21), l_dist = glm::abs(x11 - x22), r_dist = glm::abs(x12 - x21), smallest = glm::min(b_dist, glm::min(t_dist, glm::min(r_dist, l_dist)));
		if (b_dist == smallest) {
		//	printf("Result dol\n");
			return glm::vec2(0.0, -1.0);
		}
		if (t_dist == smallest) {
		//	printf("Result gora\n");
			return glm::vec2(0.0, 1.0);
		}
		if (l_dist == smallest) {
		//	printf("Result lewo \n");
			return glm::vec2(-1.0, 0.0);
		}
		if (r_dist == smallest) {
		//	printf("Result prawo\n");
			return glm::vec2(1.0, 0.0);
		}
	}
	return glm::vec2(0.0, 0.0);
}

CollisionInterface::CollisionInterface(glm::vec2* p) :position(p)
{
}

SquareCollision::SquareCollision(glm::vec2* pos, glm::vec2 _dims) : CollisionInterface(pos), dims(_dims)
{
	range = glm::length(dims / 2.f);
}

bool SquareCollision::isInRange(CollisionInterface* e)
{
	if (glm::distance(*(e->position), *(this->position)) <= +e->range + this->range) return true;
	else return false;
}

glm::vec2 SquareCollision::collide(CollisionInterface* c)
{
	return c->collideWithSquare(this);
}

glm::vec2 SquareCollision::collideWithSquare(SquareCollision* sq)
{
	return collisionSquareSquare(sq, this);
}
