#pragma once
#include "SDL_image.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* file);
	static void draw(SDL_Texture* tex, SDL_Rect &src, SDL_Rect &dest, double angle);
};

