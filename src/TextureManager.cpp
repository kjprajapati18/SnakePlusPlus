#include "TextureManager.h"
#include "Game.h"


SDL_Texture* TextureManager::LoadTexture(const char* file) {
	SDL_Surface* tmp = IMG_Load(file);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dest, double angle) {
	//SDL_RenderCopy(Game::renderer, tex, &src, &dest);
	SDL_RenderCopyEx(Game::renderer, tex, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
}