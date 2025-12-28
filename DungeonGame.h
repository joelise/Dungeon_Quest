#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Goblin.h"
#include "Minotaur.h"
#include "Tile.h"
#include "Enums.h"
#include "MoveResult.h"
#include <iostream>
#include <list>
#include <cmath>
#include <vector>
#include <algorithm>


// Texture Paths
const static std::string path_Hero = "Textures/Hero_sword.png";			// Hero
const static std::string path_Carpet[]{ "Textures/Tile_carpet_base.bmp", "Textures/Tile_carpet_blood_1.bmp", "Textures/Tile_carpet_bones.bmp"};		// Carpet
const static std::string path_Enemy{ "Textures/Enemy_orc_blue.png" };	// Enemy
const static std::string path_Boss{ "Textures/Minotaur.png" };

const int TextureAmount = sizeof(path_Carpet) / sizeof(path_Carpet[0]);	// Gets Carpet texture array length

// Room Files and Values
const static char* RoomFiles[]{ "Data/Rooms/Room01.bmp", "Data/Rooms/Room02.bmp", "Data/Rooms/Room03.bmp", "Data/Rooms/Room04.bmp", "Data/Rooms/Room05.bmp" };
const static char* BossRoom[]{ "Data/Rooms/Room01.bmp" };
const int NumRoomsX = 10;
const int NumRoomsY = 10;
const static int RoomSize = 10;

class DungeonGame
{
public:
	Tile Tiles[RoomSize][RoomSize];
	Player* Hero;
	Goblin* Enemy;
	Minotaur* Boss;
	SDL_Texture* Carpets[TextureAmount];
	SDL_Surface* CarpetSurf;
	int spawnPosX = 5;
	int spawnPosY = 5;

	int DungeonLayout[NumRoomsX][NumRoomsY];

	int CurrentRoomX;
	int CurrentRoomY;
	int RoomTypes = sizeof(RoomFiles) / sizeof(RoomFiles[0]);

	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();
	void LoadTextures(SDL_Renderer* renderer);
	void LoadBoss(SDL_Renderer* renderer);
	int RandomRoomNum();
	Direction RandomDir();
	void RandomizeDungeon();
	void RandomRoom();
	void SetNeighbour();
	void LoadRoom(const char* file);
	void LoadRoom(int x, int y);
	bool FirstWalkable(int& posX, int& posY);
	void SetPlayerPos();
	void SetEnemyPos();
	void EnemyCheck();
	void UpdateRoom(Direction dir);
	void LoadRoom(Direction dir);
	void PlayerMove(Direction dir);
	void EnemyMove(Direction dir);
	void Update(double);
	void LoadBossRoom(SDL_Renderer* renderer);
	void GetTiles();
	void StartGame(SDL_Renderer* renderer);
	void test();
	void SetHeuristic();
	int ManhattanDistance(int x1, int y1, int x2, int y2);
	void ResetTiles();
	void CheckNeighbourTile(Tile* current, Tile* target, std::vector<Tile*>& openList);
	Tile* FindLowestF(std::vector<Tile*>& openList);
	Tile* LowestNeighbour(Tile* current);
	void RemoveFromOpen(std::vector<Tile*>& openList, Tile* tile);
	std::vector<Tile*> BuildPath(Tile* startTile, Tile* targetTile);
	void FindPath();
	void Pathfinding();

	// Pathfinding A3
	Tile* HeroTile;
	Tile* BossTile;
	Tile* StartingTile;
	
	//Tile BossTile();
	
	

	// ATTEMPTED FUNCTIONS

	//bool EnemyisAlive();
	//void PlayerMovement(Direction dir, int tile);
	//void PlayerMove(Direction);
	//void PlayerMove(Direction dir);
	//void SetTile();
	//Tile* GetNeighbour(int currentX, int currentY, Direction dir);
	//Tile* FindNeighbour(Direction dir);
	//void TryMove(int x, int y, Direction dir, Tile* n);
	//MoveResult TryMove(GameCharacter* character, Direction dir);
	//void PlayerMovement(Direction dir);
	//void MovePlayer();
	//MoveResultAction SetAction(Direction dir);
	//void MoveResult(MoveResultAction action, Direction dir);
	//void TryMove(Direction dir);
	//void TryMoveResult(MoveResult& result, Direction dir);
	//void Input(Direction dir);
	//MoveResult TryMove(GameCharacter* character, Direction dir);
	//MoveResult* MoveResult;
	//void TryMove(int x, int y, GameCharacter* character, Tile* n, Direction dir);
	//MoveResult* TryMove(int currentX, int currentY, Direction dir);

private:
	float tileSizeX;
	float tileSizeY;
};


