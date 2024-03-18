#ifndef CIRCLE_COLLIDER
#define CIRCLE_COLLIDER

#include "collider.h"
class circle_collider : public collider
{
	double radius;
public:
	circle_collider(double x, double y, double radius) : 
		collider(x, y), radius(radius) {
	}

	~circle_collider() {
	}

	double get_radius() {
		return this->radius;
	}
};

#endif

