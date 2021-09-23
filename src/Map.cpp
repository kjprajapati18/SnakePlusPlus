#include "Map.h"
#include "Game.h"
#include "TextureManager.h"
#include "ECS.h"
#include "Components.h"


Map::Map() {
	/*
	//Temporary level creation
	int level[20][25];

	for (int i = 0; i < 20; i++) for (int j = 0; j < 25; j++) level[i][j] = 0;
	for (int i = 0; i < 20; i++) {
		level[i][11] = 2;
		level[i][12] = 2;
		level[i][13] = 2;
	}
	for (int i = 0; i < 20; i++) {
		level[i][0] = 1;
		level[i][24] = 1;
	}
	for (int i = 0; i < 25; i++) {
		level[0][i] = 1;
		level[19][i] = 1;
	}

	sand = TextureManager::LoadTexture("assets/sand.png");
	rock = TextureManager::LoadTexture("assets/rock.png");
	water = TextureManager::LoadTexture("assets/water.png");*/


	//IF REUSIGN WATER/ROCK/SAND, MAKE SURE TO MAKE IT 16x16
	int level[40][50];

	for (int i = 1; i < 39; i++) for (int j = 1; j < 49; j++) level[i][j] = 3; //ground

	//Border walls
	for (int i = 0; i < 40; i++) {
		level[i][0] = 4;
		level[i][49] = 4;
		level[i][1] = 4;
		level[i][48] = 4;
	}
	for (int j = 1; j < 49; j++) {
		level[0][j] = 4;
		level[39][j] = 4;
		level[1][j] = 4;
		level[38][j] = 4;
	}

	wall = TextureManager::LoadTexture("assets/wall.png");
	ground = TextureManager::LoadTexture("assets/ground.png");
	loadMap(level);
	drawWalls();
}

Map::~Map() {
//	SDL_DestroyTexture(sand);
	//SDL_DestroyTexture(rock);
	//SDL_DestroyTexture(water);
	//SDL_DestroyTexture(wall);
	//SDL_DestroyTexture(ground);
}

void Map::loadMap(int arr[40][50]) {
	for (int i = 0; i < 40; i++) for (int j = 0; j < 50; j++) map[i][j] = arr[i][j];
}

void Map::drawWalls() {

	SDL_Rect src{ 0, 0, 16, 16 };
	SDL_Rect dest{ 0, 0, 16, 16 };

	Entity* wall = nullptr;
	for (int row = 0; row < 40; row++) {
		dest.y = row * 16;
		for (int col = 0; col < 50; col++) {
			dest.x = col * 16;
			if (map[row][col] == 4) {
				wall = &Game::manager.addEntity();
				wall->addComponent<TransformComponent>(dest.x, dest.y, 16, 16, 1, 1);
				wall->addComponent<SpriteComponent>("assets/wall.png");
				wall->addComponent<ColliderComponent>("wall");
			}
		}
	}
}

void Map::drawMap() {

	SDL_Rect src{ 0, 0, 16, 16 };
	SDL_Rect dest{ 0, 0, 16, 16 };

	SDL_Renderer* ren = Game::renderer;
	Entity* wall = nullptr;

	for (int row = 0; row < 40; row++) {
		dest.y = row * 16;
		for (int col = 0; col < 50; col++) {
			dest.x = col * 16;

			switch (map[row][col]) {
				/*case 0: //Sand
					SDL_RenderCopy(ren, sand, &src, &dest);
					break;
				case 1: //Rock
					SDL_RenderCopy(ren, rock, &src, &dest);
					break;
				case 2: //Water
					SDL_RenderCopy(ren, water, &src, &dest);
					break;*/
				case 3: //Ground
					SDL_RenderCopy(ren, ground, &src, &dest);
					break;
				//case 4: //Wall
				//	//SDL_RenderCopy(ren, wall, &src, &dest);
				//	break;
				default:
					break;
			}
		}
	}
}