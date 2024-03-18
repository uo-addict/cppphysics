#ifndef DOT
#define DOT

#include "entity.h"
#include "texture.h"

class collider;

class dot : public entity
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;
	static const int DOT_VEL = 1;
	static const texture dot_texture;

	dot(int x, int y, texture* texture) : 
		entity(x, y, type::DOT_TYPE, texture) {
	}

	~dot() {

	}

	void render() {
		circle_collider* this_collider = static_cast<circle_collider*>(this->_collider);
		double radius = this_collider->get_radius();
		this->_texture->render(this->x - radius, this->y - radius);
	}

	// Moves the dot and checks collision
	void move() {
		circle_collider* this_collider = static_cast<circle_collider*>(this->_collider);
		double radius = this_collider->get_radius();

		//Move the dot left or right
		this->x += this->vx;
		this->align_collider();

		//If the dot collided or went too far to the left or right
		if ((this->x - radius < 0) || (this->x + radius > 640))
		{
			//Move back
			this->x -= this->vx;
			this->align_collider();
		}

		//Move the dot up or down
		this->y += this->vy;
		this->align_collider();

		//If the dot collided or went too far up or down
		if ((this->y - radius < 0) || (this->y + radius > 480))
		{
			//Move back
			this->y -= this->vy;
			this->align_collider();
		}
	}

	double distanceSquared(int x1, int y1, int x2, int y2)
	{
		int deltaX = x2 - x1;
		int deltaY = y2 - y1;
		return deltaX * deltaX + deltaY * deltaY;
	}

	bool check_collision(entity::type type, collider* collider) {
		circle_collider* this_collider = static_cast<circle_collider*>(this->_collider);
		switch (type) {
		case entity::type::DOT_TYPE:
			break;
		case entity::type::PADDLE_TYPE:
			rectangle_collider* r_collider = static_cast<rectangle_collider*>(collider);

			double x = r_collider->get_x();
			double y = r_collider->get_y();
			double width = r_collider->get_width();
			double height = r_collider->get_height();

			//Closest point on collision box
			int cX, cY;

			//Find closest x offset
			if (this->x < x)
			{
				cX = x;
			}
			else if (this->x > x + width)
			{
				cX = x + width;
			}
			else
			{
				cX = this->x;
			}

			//Find closest y offset
			if (this->y < y)
			{
				cY = y;
			}
			else if (this->y > y + height)
			{
				cY = y + height;
			}
			else
			{
				cY = y;
			}

			//If the closest point is inside the circle
			double radius = this_collider->get_radius();
			if (distanceSquared(this->x, this->y, cX, cY) < radius * radius)
			{
				//This box and the circle have collided
				return true;
			}

			//If the shapes have not collided
			return false;
			break;
		}
	}
};

#endif

