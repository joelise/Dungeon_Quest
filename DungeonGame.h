#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Goblin.h"
#include "Tile.h"
#include "Enums.h"
#include "MoveResult.h"
#include <iostream>


const static std::string path_Hero = "Textures/Hero_sword.png";
const static std::string path_Carpet[]{ "Textures/Tile_carpet_base.bmp", "Textures/Tile_carpet_blood_1.bmp", "Textures/Tile_carpet_bones.bmp"};
const static std::string path_Enemy[]{ "Textures/Enemy_orc_blue.png", "Textures/Enemy_orc_grey.png", "Textures/Enemy_orc_orange.png", "Textures/Enemy_orc_red.png"};

const int TextureAmount = sizeof(path_Carpet) / sizeof(path_Carpet[0]);

const static char* RoomFiles[]{ "Data/Rooms/Room01.bmp", "Data/Rooms/Room02.bmp", "Data/Rooms/Room03.bmp", "Data/Rooms/Room04.bmp", "Data/Rooms/Room05.bmp" };
const int NumRoomsX = 10;
const int NumRoomsY = 10;
const int EnemyTex = sizeof(path_Enemy) / sizeof(path_Enemy[0]);
//static int CurrentRoomX;
//static int CurrentRoomY;
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
	int RandomNum();
	int RandomDir();
	Tile Tiles[RoomSize][RoomSize];
	void RandomizeDungeon();
	void RandomRoom();
	void LoadRoom(const char* file);
	void LoadRoom(int x, int y);
	bool FirstWalkable(int& posX, int& posY);
	void SetPlayerPos();
	//void PlayerMovement(Direction dir, int tile);
	//void PlayerMove(Direction);
	//void PlayerMove(Direction dir);
	Player* Hero;
	Goblin* Enemy;
	int PlayerPosX;
	int PlayerPosY;
	int spawnPosX = 5;
	int spawnPosY = 5;

	int DungeonLayout[NumRoomsX][NumRoomsY];
	
	int CurrentRoomX;
	int CurrentRoomY;
	int RoomTypes = sizeof(RoomFiles) / sizeof(RoomFiles[0]);
	//int CarpetTypes = sizeof(path_Carpet) / sizeof(path_Carpet[0]);
	void Update(double);
	SDL_Texture* Carpets[TextureAmount];
	SDL_Surface* CarpetSurf;
	

	
	Tile* tileRef;
	//SDL_Surface* RoomSurf;
	Tile* GetNeighbour(int currentX, int currentY, Direction dir);
	void SetNeighbour();
	//Tile* FindNeighbour(Direction dir);
	//void TryMove(int x, int y, Direction dir, Tile* n);
	//MoveResult TryMove(GameCharacter* character, Direction dir);
	void UpdateRoom(Direction dir);
	void LoadRoom(Direction dir);
	//void PlayerMovement(Direction dir);
	//void MovePlayer();
	//MoveResultAction SetAction(Direction dir);
	//void MoveResult(MoveResultAction action, Direction dir);
	//void TryMove(Direction dir);
	//void TryMoveResult(MoveResult& result, Direction dir);
	//void Input(Direction dir);
	//MoveResult TryMove(GameCharacter* character, Direction dir);
	void PlayerMove(Direction dir);
	void test();
	//MoveResult* MoveResult;
	void TryMove(int x, int y, GameCharacter* character, Tile* n, Direction dir);
	//MoveResult* TryMove(int currentX, int currentY, Direction dir);

	void StartGame(SDL_Renderer* renderer);
	
private:
	float tileSizeX;
	float tileSizeY;
};


