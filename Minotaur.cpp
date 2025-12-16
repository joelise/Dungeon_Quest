#include "Minotaur.h"

Minotaur::Minotaur()
{

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
