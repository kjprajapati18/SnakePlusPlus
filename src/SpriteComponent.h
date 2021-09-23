#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

#define PI 3.14159265

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	double rotationAngle = 0.0;

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}
	void init() override {
		transform = &(entity->getComponent<TransformComponent>());

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		destRect.w = transform->width * transform->scaleW;
		destRect.h = transform->height * transform->scaleH;
	}

	void update() override {
		destRect.x = (int)transform->getX();
		destRect.y = (int)transform->getY();
	
		rotationAngle = transform->getAngle() * 180.0 / PI;
	}
	void draw() override {
		TextureManager::draw(texture, srcRect, destRect, rotationAngle);
	}
	SDL_Rect& getDestRect() {
		return destRect;
	}
};