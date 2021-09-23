#pragma once

#include "Game.h"
#include "Components.h"

class MouseComponent : public Component{
private:
	SDL_Rect* clickBox;
	
public:
	bool clicked;
	std::string name;

	MouseComponent(const std::string& tag):
	name(tag)
	{}

	void init() override{
		clicked = false;
		clickBox = &entity->getComponent<SpriteComponent>().getDestRect();
	}
	
	void update() override{
		//MouseComponents are only in MouseManager
		//MouseManager only gets called when MouseUpEvent occurs
		if(Game::event.type == SDL_MOUSEBUTTONUP){
			int x, y;
			SDL_GetMouseState(&x, &y);

			if (x >= clickBox->x &&
				x <= clickBox->x + clickBox->w &&
				y >= clickBox->y &&
				y <= clickBox->y + clickBox->h) {
				clicked = true;
			}
		}
	}


};
