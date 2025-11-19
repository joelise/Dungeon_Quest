#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
#include "Enums.h"
#include "MoveResult.h"


const static std::string path_Hero = "Textures/Hero_sword.png";
const static std::string path_Carpet[]{ "Textures/Tile_carpet_base.bmp", "Textures/Tile_carpet_blood_1.bmp", "Textures/Tile_carpet_bones"};

const int TextureAmount = sizeof(path_Carpet) / sizeof(path_Carpet[0]);

//const static std::string room_Path = "Data / Rooms / Room01.bmp";

//const char* Room[] = { "Data/Rooms/Room01.bmp" };

//const char* CarpetTiles[]{ "Textures/Tile_carpet_base.bmp" };

const static int RoomSize = 10;

class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();
	void LoadTextures(SDL_Renderer* renderer);
	void LoadRoom(const char* file);
	//void PlayerMovement(Direction dir, int tile);
	void PlayerMove(Direction);
	Player* Hero;
	int spawnPosX = 5;
	int spawnPosY = 5;

	
	void Update(double);
	SDL_Texture* Carpets[TextureAmount];
	SDL_Surface* CarpetSurf;
	Tile Tiles[RoomSize][RoomSize];

	
	Tile* tile;
	//SDL_Surface* RoomSurf;
	//Tile* GetNeighbour(int currentX, int currentY, Direction dir);
	
private:
	float tileSizeX;
	float tileSizeY;
};


