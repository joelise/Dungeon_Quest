#pragma once
#include "Tile.h"
#include "GameCharacter.h"
#include "Enums.h"

class MoveResult
{
public:
	MoveResult();
	~MoveResult();
	MoveResult(Tile* tile, MoveResultAction action);
	//MoveResult(Tile* n);
	Tile* GetTile();
	void SetAction(MoveResultAction a);
	MoveResultAction GetAction();
	//oveResult TryMove(int currentX, int currentY, Direction dir);

	
	
	

private:
	Tile* tile;
	GameCharacter* character;
	MoveResultAction action;
};

