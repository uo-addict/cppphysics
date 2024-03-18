/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "math.h"
#include "world.h"
#include "entity.h"
#include "texture.h"
#include "ai_processor.h"
#include "movement_processor.h"
#include "collision_processor.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BOARD_WIDTH = 800;
const int BOARD_HEIGHT = 600;
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;

// Attributes
const double AI_MASS = 5.0;
const double PADDLE_MOMENT = 0.0;
const double PADDLE_RADIUS = 50.0;
const double BALL_WIDTH = 20.0;
const double BALL_HEIGHT = 20.0;
const double BALL_MASS = 1.0;
const double BALL_MOMENT = 0.0;
const double BALL_RADIUS = 10.0;
const double MAX_VELOCITY = 3.0;

const SDL_Color WHITE = { 255, 255, 255};
const SDL_Color RED = { 255, 0, 0 };
const SDL_Color GREEN = { 0, 128, 0 };
const SDL_Color BLUE = { 0, 0, 255 };
const SDL_Color YELLOW = { 255, 255, 0 };

SDL_Window* sdl_window = NULL;
SDL_Renderer* sdl_renderer = NULL;\

// Texture map
std::vector<entity*> entities;

bool init(SDL_Window** sdl_window, SDL_Renderer** sdl_renderer) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	// Create window
	*sdl_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (*sdl_window == 0)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Create vsynced renderer for window
	*sdl_renderer = SDL_CreateRenderer(*sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (*sdl_renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialize renderer color
	SDL_SetRenderDrawColor(*sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	return true;
}

double distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

void clear_screen() {
	//Clear screen
	SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(sdl_renderer);
}

int main(int argc, char* args[])
{
	if (!init(&sdl_window, &sdl_renderer)) {
		printf("Failed to initialize SDL!\n");
		return 0;
	}

	// Load textures
	texture dot_texture(sdl_renderer);
	texture paddle_texture(sdl_renderer);
	dot_texture.load("dot.bmp");
	paddle_texture.load("dot.bmp");

	// Load entities
	entities.push_back(new dot(DOT_WIDTH / 2, DOT_HEIGHT / 2));
	entities.push_back(new dot(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4));

	// Create game world instance
	world world;
	world.add_processor(new ai_processor);
	world.add_processor(new collision_processor);
	world.add_processor(new movement_processor);

	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	//Set the wall
	SDL_Rect wall;
	wall.x = 300;
	wall.y = 40;
	wall.w = 40;
	wall.h = 400;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			//Handle input for the dot
			dot.handleEvent(e);
		}

		world.process();

		//Move the dot and check collision
		dot.move(wall, otherDot.getCollider());

		// Clear screen
		clear_screen();

		// Render wall
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(gRenderer, &wall);

		// Render dots
		dot.render();
		otherDot.render();

		//Update screen
		SDL_RenderPresent(gRenderer);
	}

	//Free resources and close SDL
	close();

	return 0;
}
