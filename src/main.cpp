#include <iostream>
#include <SDL.h>
#include <chrono>
#include <ctime>
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	int WIDTH = 800;
	int HEIGHT = 640;

	game = new Game("Snake++", WIDTH, HEIGHT, false);
	int frames = 0, ticks = 0;
	double delta = 0;
	auto start = std::chrono::system_clock::now();

	while (game->isRunning()) {
		frames++;
		if (delta > (double)ticks / 60) {
			game->update();
			game->render();
			ticks++;
		}
		game->handleEvent();

		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		delta += elapsed_seconds.count();
		start = std::chrono::system_clock::now();
		if (delta > 1) {
			delta--;
			std::cout << "Frames: " << frames << "\t Ticks: " << ticks << "\n";
			frames = 0; ticks = 0;
		}
	}

	delete game;
	return 0;
}