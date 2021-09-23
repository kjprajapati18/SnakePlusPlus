#pragma once
#include "SDL_image.h"

class GameObject
{

public:
	GameObject(const char* texturePath, int startX, int startY);
	~GameObject();

	void update();
	void render();

private:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Renderer* renderer;

};

