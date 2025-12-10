#pragma once
#include "GameCharacter.h"
#include "Enums.h"


class Player :
    public GameCharacter

{
public:
    //void PlayerMovement(Player* player, Direction* dir);

    //int PosX;
    //int PosY;
    //int SpawnPosX;
   // int SpawnPosY;
    
   // void SetCurrentPos(float x, float y, float tileSize);
   

    void MovePlayer(Direction dir, Player* player, float tile);
    
};

