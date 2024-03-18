#ifndef ENTITY
#define ENTITY

#include "circle_collider.h"
#include "rectangle_collider.h"
#include "texture.h"

#include <SDL.h>
#include <string>
#include <map>
#include <math.h>

class entity
{
protected:
	double x;
	double y;
	double vx = 0.0;
	double vy = 0.0;
	double ax = 0.0;
	double ay = 0.0;

	collider* _collider;
	texture* _texture;

public:
	enum type {
		DOT_TYPE,
		PADDLE_TYPE
	};

	entity(double x, double y, type type, texture* texture) : 
		x(x), y(y), _texture(texture) {

		switch (type) {
		case DOT_TYPE:
			this->_collider = new circle_collider(x, y, 10.0);
		break;
		case PADDLE_TYPE:
			this->_collider = new rectangle_collider(x, y, 5.0, 20.0);
		break;
		}
	}

	~entity() {
		if (this->_collider != 0) {
			delete this->_collider;
			this->_collider = 0;
		}
	}

	void align_collider() {
		this->_collider->x = this->x;
		this->_collider->y = this->y;
	}

	virtual void render() = 0;
	virtual void move() = 0;
	virtual bool check_collision(entity::type, collider*) = 0;

	const collider& get_collider() {
		return *_collider;
	}

	void process_event(const SDL_Event& e) {
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: this->vy -= 1.0; break;
			case SDLK_DOWN: this->vy += 1.0; break;
			case SDLK_LEFT: this->vx -= 1.0; break;
			case SDLK_RIGHT: this->vx += 1.0; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: this->vy += 1.0; break;
			case SDLK_DOWN: this->vy -= 1.0; break;
			case SDLK_LEFT: this->vx += 1.0; break;
			case SDLK_RIGHT: this->vx -= 1.0; break;
			}
		}
	}
};



#endif


