#include "MoveResult.h"

MoveResult::MoveResult()
{
	
}

MoveResult::~MoveResult()
{
	
}

MoveResult::MoveResult(Tile* n)
{
	//action = MoveResultAction::MoveOk;
	tile = n;
	(n->Walkable) ? action = MoveOk : action = Blocked;
	character = nullptr;
}

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
	return MoveResultAction();
}


