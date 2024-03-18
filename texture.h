#ifndef TEXTURE
#define TEXTURE

#include <string>
#include <SDL.h>

class texture
{
	SDL_Renderer* sdl_renderer;
	SDL_Texture* sdl_texture;

	int width;
	int height;
public:
	texture(SDL_Renderer*);
	~texture();
	bool load(std::string);
	void free();
	void set_color(SDL_Color);
	void set_blend_mode(SDL_BlendMode);
	void set_alpha(Uint8);
	void render(int x, int y, SDL_Rect* clip = 0, double angle = 0.0, SDL_Point* center = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int get_width();
	int get_height();
};

#endif

