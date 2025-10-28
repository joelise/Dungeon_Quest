#include "GameCharacter.h"

GameCharacter::GameCharacter()
{

}

GameCharacter::~GameCharacter()
{
}

void GameCharacter::Attack(GameCharacter& other)
{
}

void GameCharacter::Killed()
{
}

void GameCharacter::Update(float dt)
{
}

void GameCharacter::Collect(Pickup& pickup)
{
}

bool GameCharacter::CanMoveBetweenRooms()
{
	return false;
}

bool GameCharacter::GetIsAlive()
{
	return false;
}

SDL_FRect* GameCharacter::GetRect()
{
	return nullptr;
}
