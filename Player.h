#pragma once
#include "GameCharacter.h"
#include "Enums.h"

class Player :
    public GameCharacter
{
public:
    //void PlayerMovement(Player* player, Direction* dir);
    void MovePlayer(Direction dir, Player* player, float tile);
    
};

