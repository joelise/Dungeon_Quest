#pragma once
#include <SDL3/SDl.h>
#include "Enums.h"

class Tile
{
	static bool CompareColours(SDL_Color& col1, SDL_Color& col2);

public:
	Tile();
	int X;
	int Y;
	bool Walkable;
	SDL_Texture* texture;
	SDL_FRect Rect;
	void Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[]);
	Tile* NorthNeighbour;
	Tile* EastNeightbour;
	Tile* SouthNeighbour;
	Tile* WestNeighbour;
	bool HasEnemy;
	bool HasHero;

	Tile* GetNeighbour(Direction dir);
	
	
};

