#include "Player.h"

void Player::PlayerMovement(Player* player, Direction* dir)
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
	
}
