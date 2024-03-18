#ifndef COLLIDER
#define COLLIDER

class collider
{
	double x = 0.0;
	double y = 0.0;
	friend class entity;
public:
	collider(double x, double y) : x(x), y(y) {
	}

	~collider() {
	}

	double get_x() {
		return this->x;
	}

	double get_y() {
		return this->y;
	}
};

#endif

