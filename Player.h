#pragma once
#include "GameCharacter.h"
#include "Enums.h"

class Player :
    public GameCharacter
{
public:
    void PlayerMovement(Player* player, Direction* dir);
};

