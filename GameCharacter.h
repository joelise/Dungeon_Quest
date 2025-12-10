#pragma once
#include "Pickup.h"
#include <SDL3_image/SDL_image.h>
#include "Tile.h"
//#include "DungeonGame.h"
class GameCharacter
{

public:
	GameCharacter();	// Constructer, called when created
	~GameCharacter();	// Destructer, called when destroyed
	void SetCurrentPos(float x, float y, float tileSize);
	virtual void Attack(GameCharacter& other);
	virtual void Killed();
	virtual void Update(float dt);	// For anything time releated
	virtual void Collect(Pickup& pickup);
	virtual bool CanMoveBetweenRooms();	// False by default
	bool GetIsAlive();
	SDL_FRect* GetRect();
	SDL_Texture* Texture;
	SDL_FRect Rect;
	int PosX;
	int PosY;
	int NewPosX;
	int NewPosY;
	Tile* CurrentTile;
	

private:
	bool isAlive = true;
	//SDL_FRect rect;
};

