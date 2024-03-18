#ifndef RECTANGLE_COLLIDER
#define RECTANGLE_COLLIDER

#include "collider.h"
class rectangle_collider : public collider
{
	double width;
	double height;
public:
	rectangle_collider(double x, double y, double width, double height) : 
		collider(x, y), width(width), height(height) {
	}

	~rectangle_collider() {
	}

	double get_width() {
		return this->width;
	}

	double get_height() {
		return this->height;
	}
};

#endif

