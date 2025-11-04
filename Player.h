#pragma once
#include "GameCharacter.h"
class Player :
    public GameCharacter
{
public:
    void PlayerMovement(enum Direction*);
};

