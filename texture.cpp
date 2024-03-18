#include <string.h>
#include <stdio.h>

#include "texture.h"

#include <SDL_image.h>

texture::texture(SDL_Renderer* renderer) {
	this->sdl_renderer = renderer;
	this->sdl_texture = 0;
	this->width = 0;
	this->height = 0;
}

texture::~texture() {
	free();
}

bool texture::load(std::string path) {
	free();

	SDL_Texture* newTexture = 0;

	// Load image at specified path
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == 0)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
		if (newTexture == 0)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			// Get image dimensions
			this->width = loaded_surface->w;
			this->height = loaded_surface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	this->sdl_texture = newTexture;
	return this->sdl_texture != 0;
}

void texture::free() {
	if (this->sdl_texture != 0)
	{
		SDL_DestroyTexture(sdl_texture);
		this->sdl_texture = 0;
		this->width = 0;
		this->height = 0;
	}
}

void texture::set_color(SDL_Color color) {
	SDL_SetTextureColorMod(this->sdl_texture, color.r, color.g, color.b);
}

void texture::set_blend_mode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(this->sdl_texture, blending);
}

void texture::set_alpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(this->sdl_texture, alpha);
}

void texture::render(int x, int y, SDL_Rect* clip = 0, double angle = 0.0,
	SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
	SDL_Rect render_quad = { x, y, this->width, this->height };

	if (clip != NULL)
	{
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, sdl_texture, clip, &render_quad, angle, center, flip);
}
int texture::get_width() {
	return this->width;
}

int texture::get_height() {
	return this->height;
}