#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturePath, int startX, int startY)
{
	renderer = Game::renderer;
	texture = TextureManager::LoadTexture(texturePath);
	
	srcRect.h = 32; srcRect.w = 32;

	int scale = 2;
	destRect.x = startX; destRect.y = startY;
	destRect.h = srcRect.h * scale;
	destRect.w = srcRect.w * scale;
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	int speed = 5;
	if (destRect.y <= 0)destRect.x += speed;
	if (destRect.x >= Game::windowWidth - destRect.w) destRect.y += speed;
	if (destRect.y >= Game::windowHeight - destRect.h) destRect.x -= speed;
	if (destRect.x <= 0) destRect.y -= speed;
}

void GameObject::render()
{
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
