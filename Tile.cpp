#include "Tile.h"

bool Tile::CompareColours(SDL_Color& col1, SDL_Color& col2)
{
	return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
}

void Tile::Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[])
{
	SDL_Color black = { 0, 0, 0, 255 };
	//Rect = { x, y, size, size };

	if (CompareColours(color, black))
	{
		Walkable = false;
	}
	else
	{
		Walkable = true;
		this->texture = textures[0];
	}

	SDL_FRect rect{ Rect.x = x * size, Rect.y = y * size, Rect.w = size, Rect.h = size };
	

	this->Rect = rect;
}
