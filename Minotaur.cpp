#include "Minotaur.h"

Minotaur::Minotaur()
{
	PathIndex = 0;
}

Minotaur::~Minotaur()
{
}

void Minotaur::CurrentPos(float x, float y, float tileSize)
{
	PosX = x;
	PosY = y;
	this->Rect.x = x * tileSize;
	this->Rect.y = y * tileSize;
	this->Rect.h = tileSize;
	this->Rect.w = tileSize;
}

void Minotaur::MoveBoss()
{
	
	PathIndex = 0;

	if (CurrentPath.empty() || PathIndex > sizeof(CurrentPath.size() - 1))
	{
		return;
	}

	PathIndex++;
	Tile* nextTile = CurrentPath[PathIndex];
	CurrentTile = nextTile;
	PosX = CurrentTile->X;
	PosY = CurrentTile->Y;
}
