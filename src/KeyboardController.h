#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "SDL.h"

class KeyboardController : public Component{
	TransformComponent* transform= nullptr;
	bool up, down, left, right, dualVer, dualHor;
	int speed = 4;
	float angleChange = 0.08;

public:
	void init() {
		transform = &(entity->getComponent<TransformComponent>());
		up = down = left = right = dualVer = dualHor = false;
	}
	void update() override {
		float angle = transform->getAngle();
		Vector2D& accel = transform->getAccel();
		Vector2D& velocity = transform->getVel();

		angle += accel.x * angleChange;	
		transform->setAngle(angle);
		velocity.x = cos(angle) * speed;
		velocity.y = sin(angle) * speed;
	}
	void eventUpdate(){
		if (Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				up = true;
				break;
			case SDLK_a:
				left = true;
				break;
			case SDLK_s:
				down = true;
				break;
			case SDLK_d:
				right = true;
				break;
			case SDLK_ESCAPE:
				if (!Game::pause) {
					Game::pauseGame();
				}
				else {
					Game::unpauseGame();
				}
			default:
				break;
			}
		}
		
		if (Game::event.key.type == SDL_KEYUP && Game::event.key.repeat == 0) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				up = false;
				break;
			case SDLK_a:
				left = false;
				break;
			case SDLK_s:
				down = false;
				break;
			case SDLK_d:
				right = false;
				break;
			default:
				break;
			}
		}
		if (down) {
			speed = 0;
		}
		else {
			speed = 4;
		}
		if (left && right) {
			if (!dualHor) {
				dualHor = true;
				transform->getAccel().x *= -1;
			}
		}
		else {
			dualHor = false;
			if (left) {
				transform->getAccel().x = -1;
			}
			else if (right) {
				transform->getAccel().x = 1;
			}
			else {
				transform->getAccel().x = 0;
			}
		}
	}
};