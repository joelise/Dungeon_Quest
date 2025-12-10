#include "Player.h"

/*void Player::PlayerMovement(Player* player, Direction* dir)
{
	int newX = player->Rect.x;
	int newY = player->Rect.y;

	switch (*dir)
	{
	case North: newY--; break;
	case East: newX++; break;
	case South: newY++; break;
	case West: newX--; break;
	}
	
}*/

/*void Player::SetCurrentPos(float x, float y, float tileSize)
{
	PosX = x;
	PosY = y;
	this->Rect.x = x * tileSize;
	this->Rect.y = y * tileSize;
	this->Rect.h = tileSize;
	this->Rect.w = tileSize;
}*/

void Player::MovePlayer(Direction dir, Player* player, float tile)
{

	switch (dir)
	{
	case North: this->Rect.y -= tile; break;
	case East: this->Rect.x += tile; break;
	case South: this->Rect.y += tile; break;
	case West: this->Rect.x -= tile; break;
	}
}
