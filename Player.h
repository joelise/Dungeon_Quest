#pragma once
#include "GameCharacter.h"

class Player :
    public GameCharacter
{
public:
    DungeonGame* game;
    void PlayerMovement(Player* player, Direction* dir);
};

