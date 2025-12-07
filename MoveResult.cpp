#include "MoveResult.h"

MoveResult::MoveResult()
{
	
}

MoveResult::~MoveResult()
{
	
}

MoveResult::MoveResult(Tile* tile, MoveResultAction action)
{
	this->tile = tile;
	this->action = action;
	this->character = nullptr;
}

/*MoveResult::MoveResult(Tile* n)
{
	action = MoveResultAction::Undefined;
	tile = n;
	character = nullptr;
}*/
 
Tile* MoveResult::GetTile()
{
	return tile;
}

void MoveResult::SetAction(MoveResultAction a)
{
	action = a;
}

MoveResultAction MoveResult::GetAction()
{
	return action;
}

/*MoveResult MoveResult::TryMove(int currentX, int currentY, Direction dir)
{
	MoveResult result;

	switch (result.action)
	{
	case MoveOk: tile->Walkable == true; break;
	case Blocked: tile->Walkable == false; break;
	case LoadNewRoom: tile == nullptr; break;
	}

	

	return result;
	//return MoveResult();
}*/




