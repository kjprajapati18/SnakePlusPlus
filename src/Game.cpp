#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "SpriteComponent.h"
#include "StateHandler.h"

Map* Game::map = nullptr;

int Game::windowHeight;
int Game::windowWidth;

bool Game::pause = false;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager Game::manager;
Manager Game::mouseManager;
Component* Game::keyboardHandler = nullptr;

GAME_STATE StateHandler::state;

SDL_Surface* iconSurface;

//TODO:
//Add Random Food Generation
//Make a GameOver Screen and Replay/BackToMenu button for after collision
//Make Snake Grow (LinkedList-like Tail)
//Score System for GameOver

//Multiplayer Menu for checking connections

//Server stuff



Game::Game(const char* title, int width, int height, bool fullScreen) {
	windowWidth = width;
	windowHeight = height;

	init(title, width, height, fullScreen);
}

Game::~Game() {

	clean();

}

void Game::init(const char* title, int width, int height, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL was not Initialized" << std::endl;
		running = false;
		return;
	}
	std::cout << "SDL was initialized!!\n";

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	std::cout << "Window created sucessfully\n";

	iconSurface = SDL_LoadBMP("assets/playerhead.bmp");
	SDL_SetWindowIcon(window, iconSurface);
	std::cout << "Icon created succesfully\n";

	renderer = SDL_CreateRenderer(window, -1, 0);
	std::cout << "Renderer created successfully" << std::endl;
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	
	StateHandler::state;
	StateHandler::initMenu();
	
	running = true;
}

void Game::handleEvent()
{
	Entity* select = nullptr;

	if(SDL_PollEvent(&event) == 0) return;

	switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if (keyboardHandler != nullptr) {
				static_cast<KeyboardController*>(keyboardHandler)->eventUpdate();
			}
			break;

		case SDL_MOUSEBUTTONUP:
			mouseManager.update();
			select = StateHandler::findClicked();
			if (select != nullptr) {
				std::string& selectName = select->getComponent<MouseComponent>().name;
				StateHandler::changeState(selectName);
			}
			break;

		case SDL_QUIT:
			running = false;
			break;

		default:
			break;
	}
	SDL_PumpEvents();
	SDL_FlushEvent(event.type);
}

void Game::update()
{

	manager.refresh();
	mouseManager.refresh();

	switch (StateHandler::state) {
	case GAME_STATE::MENU:
		manager.update();
		mouseManager.update();
		break;
	case GAME_STATE::SINGLE:
		if (!pause) manager.update();
		mouseManager.update();
		break;
	case GAME_STATE::MULTIMENU:
	case GAME_STATE::MULTIGAME:
	case GAME_STATE::OPTIONS:
		manager.update();
		mouseManager.update();
		break;
	case GAME_STATE::GAMEOVER_SINGLE:
	case GAME_STATE::GAMEOVER_MULTI:
		break;
	default:
		std::cout << "Invalid Game State Update" << std::endl;
		break;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//Draw stuff here******************************************


	switch (StateHandler::state) {
	case GAME_STATE::MENU:
		break;
	case GAME_STATE::SINGLE:
		map->drawMap();
		break;
	case GAME_STATE::MULTIMENU:
	case GAME_STATE::MULTIGAME:
	case GAME_STATE::OPTIONS:
	case GAME_STATE::GAMEOVER_SINGLE:
	case GAME_STATE::GAMEOVER_MULTI:
		break;
	default:
		std::cout << "Invalid Game State Draw" << std::endl;
		break;
	}

	manager.draw();
	mouseManager.draw();

	//**********************************************************
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete map;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	SDL_FreeSurface(iconSurface);
	std::cout << "Everything was cleaned!\n";
}

bool Game::isRunning()
{
	return running;
}

void Game::clearManagers() {
	manager.clean();
	mouseManager.clean();
}

//MOVE THIS TO STATEHANDLER.H
void Game::pauseGame() {
	if (StateHandler::state != GAME_STATE::SINGLE) return;

	pause = true;
	Entity& pauseSym = mouseManager.addEntity();
	pauseSym.addComponent<TransformComponent>(290, 80, 80, 227, 1, 1);
	pauseSym.addComponent<SpriteComponent>("assets/pauseStatus.png");
	pauseSym.addComponent<MouseComponent>("Pause");

	Entity& back = mouseManager.addEntity();
	back.addComponent<TransformComponent>(215, 470, 80, 384, 1, 1);
	back.addComponent<SpriteComponent>("assets/backButton.png");
	back.addComponent<MouseComponent>("Back");
}

void Game::unpauseGame() {
	mouseManager.clean();
	pause = false;
	//Change to delete only the pause and back ocmponents (when we have more clickable stuff)
}