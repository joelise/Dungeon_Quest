#pragma once
#include <SDL3_image/SDL_image.h>
#include "Tile.h"
#include <vector>
class Minotaur
{
public:
	Minotaur();
	~Minotaur();
	void CurrentPos(float x, float y, float tileSize);
	SDL_Texture* Texture;
	SDL_FRect Rect;
	int PosX;
	int PosY;
	int NewPosX;
	int NewPosY;
	Tile* CurrentTile;

	std::vector<Tile*> CurrentPath;
	int PathIndex;
	void MoveBoss();

	
};

