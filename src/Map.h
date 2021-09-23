#pragma once
#include "SDL_image.h"

class Map
{
public:
	Map();
	~Map();

	void loadMap(int arr[40][50]);
	void drawMap();
	void drawWalls();

private:

	SDL_Texture* sand;
	SDL_Texture* rock;
	SDL_Texture* water;
	SDL_Texture* wall;
	SDL_Texture* ground;


	int map[40][50];
};

