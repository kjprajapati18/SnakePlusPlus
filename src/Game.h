#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include <iostream>
#include "SDL_image.h"

#include "ECS.h"
#include "Map.h"

class Game
{
public:
	static int windowWidth, windowHeight;
	static bool pause;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static Manager manager;
	static Manager mouseManager;
	static Component* keyboardHandler;

	static Map* map;

	static void clearManagers();
	static void pauseGame();
	static void unpauseGame();

	Game(const char* title, int width, int height, bool fullScreen);
	~Game();
	void init(const char* title, int width, int height, bool fullScreen);

	void handleEvent();
	void update();
	void render();
	void clean();

	bool isRunning();
private:
	bool running = false;
	SDL_Window* window = nullptr;
	int count = 0;

};


#endif
