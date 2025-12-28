#pragma once
#include <SDL3/SDl.h>
#include "Enums.h"
#include <climits>

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
	Tile* EastNeighbour;
	Tile* SouthNeighbour;
	Tile* WestNeighbour;
	
	// PathFinding A3
	void ResetTile();
	Tile* Parent;
	int g;
	int h;
	int f;
	bool InClosed;
	bool InOpen;

	int EstimatedF();
};

