#pragma once
#include "Game.h"
#include "SDL.h"
#include "Components.h"


enum class GAME_STATE { MENU, SINGLE, MULTIMENU, MULTIGAME, OPTIONS, GAMEOVER_SINGLE, GAMEOVER_MULTI };
int buttonWidth = 384;
int buttonHeight = 80;

class StateHandler {
public:
	static GAME_STATE state;

	static void initMenu() {

		Game::clearManagers();
		state = GAME_STATE::MENU;
		

		Entity& bg = Game::manager.addEntity();
		bg.addComponent<TransformComponent>(0, 0, Game::windowHeight, Game::windowWidth, 1, 1);
		bg.addComponent<SpriteComponent>("assets/menuBG.png");

		Entity& start = Game::mouseManager.addEntity();
		start.addComponent<TransformComponent>(210, 250, buttonHeight, buttonWidth, 1, 1);
		start.addComponent<SpriteComponent>("assets/sPlayButton.png");
		start.addComponent<MouseComponent>("Start");

		Entity& multi = Game::mouseManager.addEntity();
		multi.addComponent<TransformComponent>(210, 360, buttonHeight, buttonWidth, 1, 1);
		multi.addComponent<SpriteComponent>("assets/mPlayButton.png");
		multi.addComponent<MouseComponent>("Multi");

		Entity& options = Game::mouseManager.addEntity();
		options.addComponent<TransformComponent>(210, 470, buttonHeight, buttonWidth, 1, 1);
		options.addComponent<SpriteComponent>("assets/optionButton.png");
		options.addComponent<MouseComponent>("Options");
	}

	static void initSingle() {

		Game::clearManagers();
		Game::map = new Map();

		Entity& player = Game::manager.addEntity();
		/*TransformComponent& transform=*/ player.addComponent<TransformComponent>(32*2, 32*2, 32, 32, 1, 1);
		player.addComponent<SpriteComponent>("assets/playerhead.png");
		Game::keyboardHandler = &(player.addComponent<KeyboardController>());
		player.addComponent<ColliderComponent>("player");
	}

	

	static void initMulti() {
		//Game::clearManagers();
		//temp
		initSingle();
	}

	static void initOptions() {

		Game::clearManagers();

		Entity& back = Game::mouseManager.addEntity();
		back.addComponent<TransformComponent>(210, 470, buttonHeight, buttonWidth, 1, 1);
		back.addComponent<SpriteComponent>("assets/backButton.png");
		back.addComponent<MouseComponent>("Back");
	}

	static Entity* findClicked() {
		for (auto& e : Game::mouseManager.entities) {
			auto& mouse = e->getComponent<MouseComponent>();
			if (mouse.clicked) return mouse.entity;
		}
		return nullptr;
	}

	static void changeState(const std::string& action) {
		//Change mouse component String to new enum later
		//Change this stuff to a switch case afterwards

		if (action == "Pause") {
			Game::unpauseGame();
			return;
		}

		if (state == GAME_STATE::SINGLE) {
			delete Game::map;
			Game::map = nullptr;
			Game::keyboardHandler = nullptr;
		}

		if (action == "Start") {
			state = GAME_STATE::SINGLE;
			initSingle();
		}
		else if (action == "Multi") {
			state = GAME_STATE::MULTIGAME;
			initMulti();
		}
		else if (action == "Options") {
			state = GAME_STATE::OPTIONS;
			initOptions();
		}
		else if (action == "Back") {
			if (Game::pause) Game::unpauseGame();
			initMenu();
		}
	}
};