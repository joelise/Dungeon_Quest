#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
#include "Enums.h"

const static std::string path_Hero = "Textures/Hero_sword.png";
const static std::string path_Carpet[]{ "Textures/Tile_carpet_base.bmp" };
//const char* rooms{ "Data/Rooms/Room01.bmp" };

//const char* CarpetTiles[]{ "Textures/Tile_carpet_base.bmp" };

const static int RoomSize = 10;

class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();
	void LoadTextures(SDL_Renderer* renderer);
	void LoadRoom(const char* file);
	void PlayerMovement(Direction dir, int tile);
	Player* Hero;
	Tile Tiles[RoomSize][RoomSize];
	void Update(double);
	//SDL_Texture* carpets[3];
	Tile* tile;
	//SDL_Surface* RoomSurf;
	
private:
	float tileSizeX;
	float tileSizeY;
};


