#pragma once

#include <string>
#include "SDL.h"
#include "Components.h"
#include "Collision.h"

class ColliderComponent : public Component
{
public:
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(const std::string& name) :
		tag(name)
	{}
		
	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &(entity->getComponent<TransformComponent>());
	
	}

	void update() override {
		if (!entity->hasComponent<KeyboardController>()) return;
		for (auto& e : Game::manager.getEntities()) {
			if (e.get() == entity) continue;
			if (!e->hasComponent<ColliderComponent>()) continue;
			if (Collision::A2B(*transform, e->getComponent<TransformComponent>())) {
				std::cout << tag << " collided with " << e->getComponent<ColliderComponent>().tag << std::endl;
			}
		}
	}
};