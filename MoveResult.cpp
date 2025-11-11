#include "MoveResult.h"

MoveResult::MoveResult()
{
}

MoveResult::~MoveResult()
{
	
}

MoveResult::MoveResult(Tile* n)
{
	action = MoveResultAction::MoveOk;
	tile = n;
	character = nullptr;
}

Tile* MoveResult::GetTile()
{
	return nullptr;
}

void MoveResult::SetAction(MoveResultAction a)
{
}

MoveResultAction MoveResult::GetAction()
{
	return MoveResultAction();
}
