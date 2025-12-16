#include "DungeonGame.h"



DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{
	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
	
	srand(time(NULL));	// Seeds random number generator (resets so the rand() doesn't return the same result)
}

DungeonGame::~DungeonGame()
{
	delete this->Hero;
	delete this->Enemy;
	delete this->Boss;
}

void DungeonGame::LoadTextures(SDL_Renderer* renderer)
{
	// Loads Player
	this->Hero = new Player;
	this->Hero->Texture = IMG_LoadTexture(renderer, path_Hero.c_str());		// Player Texture
	SDL_SetTextureScaleMode(this->Hero->Texture, SDL_SCALEMODE_NEAREST);	// Scales Texture
	
	// Loads Enemy
	this->Enemy = new Goblin;
	this->Enemy->Texture = IMG_LoadTexture(renderer, path_Enemy.c_str());	// Enemy Texture
	SDL_SetTextureScaleMode(this->Enemy->Texture, SDL_SCALEMODE_NEAREST);	// Scales Texture

	this->Boss = new Minotaur;
	this->Boss->Texture = IMG_LoadTexture(renderer, path_Boss.c_str());		// Player Texture
	SDL_SetTextureScaleMode(this->Boss->Texture, SDL_SCALEMODE_NEAREST);

	// Loads Carpet Textures
	for (int i = 0; i < TextureAmount; i++)
	{
		CarpetSurf = SDL_LoadBMP(path_Carpet[i].c_str());					// Carpet Surface
		Carpets[i] = SDL_CreateTextureFromSurface(renderer, CarpetSurf);	// Carpet Texture
		SDL_SetTextureScaleMode(Carpets[i], SDL_SCALEMODE_NEAREST);			// Scales Texture
		SDL_DestroySurface(CarpetSurf);										// Release memory by deleting the surface 
	}
}

void DungeonGame::LoadBoss(SDL_Renderer* renderer)
{
	
	this->Boss->CurrentPos(0, 0, tileSizeX);
	std::cout << "Boss loaded" << std::endl;
}

int DungeonGame::RandomRoomNum()
{
	return rand() % RoomTypes;		// Returns a random number from RoomType var to choose Room file
}

Direction DungeonGame::RandomDir()
{
	int dir = rand() % 4;
	return static_cast <Direction>(dir);	// Returns a direction from an int (converts between enum and int)
}

void DungeonGame::RandomizeDungeon()
{
	// Loops through the amount of rooms in the dungeon from NumRooms X and Y
	for (int x = 0; x < NumRoomsX; x++)
	{
		for (int y = 0; y < NumRoomsY; y++)
		{
			DungeonLayout[x][y] = RandomRoomNum();		// Set a Random Room type for each room in DungeonLayout
		}
	}
}

void DungeonGame::RandomRoom()
{
	CurrentRoomX = rand() % NumRoomsX;		// Selects Random value from NumRoomsX
	CurrentRoomY = rand() % NumRoomsY;		// Selects Random value from NumRoomsY
}


void DungeonGame::SetNeighbour()
{
	for (int x = 0; x < RoomSize; x++)
	{
		for (int y = 0; y < RoomSize; y++)
		{
			Tile* tile = &Tiles[x][y];
			
			// (condition) ? true : false
			
			// Sets North Tile Neighbour, if current y == 0 player is at the top of the grid - there is no north tile
			(y == 0) ? tile->NorthNeighbour = nullptr : tile->NorthNeighbour = &Tiles[x][y - 1];	
			
			// Sets East Tile Neighbour, if current x == roomsize - 1, player is a the right side of the grid - there is no east tile
			(x == RoomSize - 1) ? tile->EastNeightbour = nullptr : tile->EastNeightbour = &Tiles[x + 1][y];

			// Sets South Tile Neighbour, if y == roomsize - 1, player is at the bottom of the grid - there is no south tile
			(y == RoomSize - 1) ? tile->SouthNeighbour = nullptr : tile->SouthNeighbour = &Tiles[x][y + 1];

			// Sets West Tile Neighbour, if x == 0 player is a the left side of the grid - there is no west tile
			(x == 0) ? tile->WestNeighbour = nullptr : tile->WestNeighbour = &Tiles[x - 1][y];
		}
	}
}

void DungeonGame::LoadRoom(const char* file)
{
	for (int x = 0; x < RoomSize; x++)
	{
		for (int y = 0; y < RoomSize; y++)
		{
			this->Tiles[x][y] = Tile();		// Resets tiles when loading new room
			SetNeighbour();					// Sets new tile values
		}
	}

	SDL_Surface* surface = SDL_LoadBMP(file);
	
	const SDL_PixelFormatDetails* pixelDetails = SDL_GetPixelFormatDetails(surface->format);
	const Uint8 bpp = SDL_BYTESPERPIXEL(surface->format);
	SDL_Color col;		 
	
	for (int y = 0; y < surface->h; y++) 
	{
		for (int x = 0; x < surface->w; x++) 
		{
			Uint8* pixel = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bpp;
			SDL_GetRGB(*reinterpret_cast<Uint32*>(pixel), pixelDetails, NULL, &col.r, &col.g, &col.b);
			
			this->Tiles[x][y].Configure(col, x * tileSizeX, y * tileSizeY, tileSizeX, Carpets);
		}
	}

	SDL_DestroySurface(surface);
}

void DungeonGame::LoadRoom(int x, int y)
{
	int index = DungeonLayout[x][y];			// Gets the int value of the set room in the dungeon from x and y input
	const char* fileName = RoomFiles[index];	// Gets RoomFile from the value in the array

	LoadRoom(fileName);		// Loads the selected room file
}

bool DungeonGame::FirstWalkable(int& posX, int& posY)
{
	// Loops to find first walkable tile and returns true
	for (int x = 0; x < RoomSize; x++)
	{
		for (int y = 0; y < RoomSize; y++)
		{
			if (Tiles[x][y].Walkable)
			{
				posX = x;
				posY = y;
				return true;
			}
		}
	}
	return false;	// Otherwise returns false
}

void DungeonGame::SetPlayerPos()
{
	// If the Tiles are walkable Set the Heros position and update their current tile
	if (FirstWalkable(spawnPosX, spawnPosY))		 
	{
		this->Hero->SetCurrentPos(spawnPosX, spawnPosY, tileSizeX);
		this->Hero->CurrentTile = &Tiles[spawnPosX][spawnPosY];
	}
}

void DungeonGame::SetEnemyPos()
{
	// Sets Enemy start pos for each room file
	int index = DungeonLayout[CurrentRoomX][CurrentRoomY];
	const char* fileName = RoomFiles[index];

	// Sets Enemy in the same postion each time the room file is loaded
	if (RoomFiles[index] == RoomFiles[0]) this->Enemy->SetCurrentPos(5, 5, tileSizeX);
	if (RoomFiles[index] == RoomFiles[1]) this->Enemy->SetCurrentPos(2, 2, tileSizeX);
	if (RoomFiles[index] == RoomFiles[2]) this->Enemy->SetCurrentPos(5, 5, tileSizeX);
	if (RoomFiles[index] == RoomFiles[3]) this->Enemy->SetCurrentPos(8, 1, tileSizeX);
	if (RoomFiles[index] == RoomFiles[4]) this->Enemy->SetCurrentPos(5, 4, tileSizeX);
}
 

void DungeonGame::EnemyCheck()
{
	// If the Hero and Enemy have the same PosX and PosY, the enemy dies

	if (this->Hero->PosX == this->Enemy->PosX && this->Hero->PosY == this->Enemy->PosY)
	{
		this->Enemy->IsAlive = false;
	}
}

void DungeonGame::UpdateRoom(Direction dir)
{
	// Updates the RoomValue from the Set DungeonLayout from the direction moved
	switch (dir)
	{
	case North: CurrentRoomY--; break;
	case East: CurrentRoomX++; break;
	case South: CurrentRoomY++; break;
	case West: CurrentRoomX--; break;
	}
}

void DungeonGame::LoadRoom(Direction dir)
{
	int nextRoomX = CurrentRoomX;
	int nextRoomY = CurrentRoomY;

	// Gets the Neighbouring rooms from the direction
	switch (dir)
	{
	case North: nextRoomY = CurrentRoomY - 1; break;
	case East: nextRoomX = CurrentRoomX + 1; break;
	case South: nextRoomY = CurrentRoomY + 1; break;
	case West: nextRoomX = CurrentRoomX - 1; break;
	}

	// Sets boundaries on the edges of the dungeon - returns if there is no more rooms
	if (nextRoomX < 0 || nextRoomX > NumRoomsX - 1 || nextRoomY < 0 || nextRoomY > NumRoomsY - 1) return;

	UpdateRoom(dir);					// Updates Current Room value
	LoadRoom(nextRoomX, nextRoomY);		// Loads NewRoom File
	this->Enemy->IsAlive = true;		// Resets enemy bool for the new room
	SetEnemyPos();						// Sets Enemy position
	

	int posX = this->Hero->PosX;
	int posY = this->Hero->PosY;

	// Sets Hero position to the oposite side from the direction they where moving (if they enter right room their pos is set on the left seemlessly)
	switch (dir)
	{
	case North: this->Hero->SetCurrentPos(posX, RoomSize - 1, tileSizeX); break;
	case East:this->Hero->SetCurrentPos(0, posY, tileSizeX); break;
	case South:this->Hero->SetCurrentPos(posX, 0, tileSizeX); break;
	case West: this->Hero->SetCurrentPos(RoomSize - 1, posY, tileSizeX); break;
	}

	this->Hero->CurrentTile = &Tiles[this->Hero->PosX][this->Hero->PosY];		// Updates Hero current tile
}

void DungeonGame::PlayerMove(Direction dir)
{
	int posX = this->Hero->PosX;
	int posY = this->Hero->PosY;
	this->Hero->CurrentTile = &Tiles[posX][posY];
	
	int dirX = 0;
	int dirY = 0;

	// Updates tile grid position based off direction
	switch (dir)
	{
	case North: dirY = -1; break;
	case East: dirX = 1; break;
	case South: dirY = 1; break;
	case West: dirX = -1; break;
	}

	// New Position = current pos and direction their moving
	int newX = this->Hero->PosX + dirX;
	int newY = this->Hero->PosY + dirY;

	Tile* target = nullptr;							// Tile Hero is moving to
	Tile* current = this->Hero->CurrentTile;		// Current Tile

	// Gets the neighbour of the current tile
	switch (dir)
	{
	case North: target = current->NorthNeighbour; break;
	case East: target = current->EastNeightbour; break;
	case South: target = current->SouthNeighbour; break;
	case West: target = current->WestNeighbour; break;
	}

	if (target == nullptr)
	{
		// If there is no tile hero is at edge of room, load the new room
		LoadRoom(dir);		// Loads room based of movement direction
		return;
	}

	if (target->Walkable)
	{
		// If the target tile is walkable move the Hero
		this->Hero->SetCurrentPos(newX, newY, tileSizeX);
		this->Hero->CurrentTile = &Tiles[newX][newY];
	}
}

void DungeonGame::EnemyMove(Direction dir)
{
	int posX = this->Enemy->PosX;
	int posY = this->Enemy->PosY;
	this->Enemy->CurrentTile = &Tiles[posX][posY];

	int dirX = 0;
	int dirY = 0;

	// Updates tile grid position based off direction
	switch (dir)
	{
	case North: dirY = -1; break;
	case East: dirX = 1; break;
	case South: dirY = 1; break;
	case West: dirX = -1; break;
	}

	int newX = this->Enemy->PosX + dirX;
	int newY = this->Enemy->PosY + dirY;

	Tile* target = nullptr;							// Tile enemy is moving to
	Tile* current = this->Enemy->CurrentTile;		// Enemy current tile

	// Gets the neighbour of the current tile
	switch (dir)
	{
	case North: target = current->NorthNeighbour; break;
	case East: target = current->EastNeightbour; break;
	case South: target = current->SouthNeighbour; break;
	case West: target = current->WestNeighbour; break;
	}
	
	if (target == nullptr) return;			// If the enemy tries to move out of the room return

	if (target->Walkable)
	{
		// If the target tile is walkable move the Enemy
		this->Enemy->SetCurrentPos(newX, newY, tileSizeX);
		this->Enemy->CurrentTile = &Tiles[newX][newY];
	}
}

void DungeonGame::Update(double)
{
	// Waits to try to move enemy
	static int movementCooldown = 0;

	if (movementCooldown > 0)
	{
		movementCooldown--;
		return;
	}
	movementCooldown = 1500;
	Direction dir = RandomDir();		// Gets a random direction to move enemy
	
	EnemyMove(dir);						// Trys to move enemy
}

void DungeonGame::LoadBossRoom(SDL_Renderer* renderer)
{
	const char* bossRoom = BossRoom[0];

	LoadRoom(bossRoom);
	SetNeighbour();
	LoadTextures(renderer);
	SetPlayerPos();
	LoadBoss(renderer);
}


void DungeonGame::StartGame(SDL_Renderer* renderer)
{
	// Functions to run at the start of the game
	RandomizeDungeon();
	RandomRoom();
	LoadRoom(CurrentRoomX, CurrentRoomY);
	SetNeighbour();
	LoadTextures(renderer);
	SetPlayerPos();
	SetEnemyPos();
	EnemyCheck();
}

void DungeonGame::test()
{
	// Testing function
	int posx = this->Hero->PosX;
	int posy = this->Hero->PosY;
	
	std::cout << posx << posy << std::endl;
	Tile& tile = Tiles[posx][posy];
	int randomDir = RandomDir();
	
}

// ATTEMPTED FUNCTIONS AND CODE (code that was tried but didn't quite work or was changed)

/*Tile* DungeonGame::GetNeighbour(int currentX, int currentY, Direction dir)
{
	switch (dir)
	{
	case North:
		if (currentY == 0) return nullptr;
		return &Tiles[currentX][currentY - 1];

	case East:
		if (currentX == RoomSize - 1) return nullptr;
		return &Tiles[currentX + 1][currentY];

	case South:
		if (currentY == RoomSize - 1) return nullptr;
		return &Tiles[currentX][currentY + 1];

	case West:
		if (currentX == 0) return nullptr;
		return &Tiles[currentX - 1][currentY];
	}
}*/
/* Tile* DungeonGame::FindNeighbour(Direction dir)
{
	Tile* target = nullptr;
	int posX = this->Hero->PosX;
	int posY = this->Hero->PosY;
	this->Hero->CurrentTile = &Tiles[posX][posY];
	Tile* current = this->Hero->CurrentTile;

	switch (dir)
	{
	case North: target = current->NorthNeighbour; return target;
	case East: target = current->EastNeightbour; return target;
	case South: target = current->SouthNeighbour;return target;
	case West: target = current->WestNeighbour; return target;
	}
}


MoveResult DungeonGame::TryMove(GameCharacter* character, Direction dir)
{
	Tile* target = GetNeighbour(character->PosX, character->PosY, dir);

	if (target == nullptr) return MoveResult(nullptr, MoveResultAction::LoadNewRoom);
	if (!target->Walkable) return MoveResult(target, MoveResultAction::Blocked);
	if (target->Walkable)
	{
		PlayerMovement(dir);
		return MoveResult(target, MoveResultAction::MoveOk);
	}
	//character->PosX = target->X;
	//character->PosY = target->Y;

	//character->SetCurrentPos(character->PosX, character->PosY, tileSizeX);
	//character->CurrentTile = &Tiles[character->PosX][character->PosY];

	//return MoveResult(target, MoveResultAction::MoveOk);
}


void DungeonGame::PlayerMovement(Direction dir)
{
	int posX = this->Hero->PosX;
	int posY = this->Hero->PosY;
	this->Hero->CurrentTile = &Tiles[posX][posY];

	int dirX = 0;
	int dirY = 0;

	switch (dir)
	{
	case North: dirY = -1; break;
	case East: dirX = 1; break;
	case South: dirY = 1; break;
	case West: dirX = -1; break;
	}

	int newX = this->Hero->PosX + dirX;
	int newY = this->Hero->PosY + dirY;

	this->Hero->NewPosX = newX;
	this->Hero->NewPosY = newY;
}


void DungeonGame::MovePlayer()
{
	this->Hero->SetCurrentPos(this->Hero->NewPosX, this->Hero->NewPosY, tileSizeX);
	this->Hero->CurrentTile = &Tiles[this->Hero->NewPosX][this->Hero->NewPosY];

	this->Hero->PosX = this->Hero->NewPosX;
	this->Hero->PosY = this->Hero->NewPosY;
	this->Hero->CurrentTile = &Tiles[this->Hero->PosX][this->Hero->PosY];
}


MoveResultAction DungeonGame::SetAction(Direction dir)
{
	MoveResultAction action;
	int posX = this->Hero->PosX;
	int posY = this->Hero->PosY;
	this->Hero->CurrentTile = &Tiles[posX][posY];

	//Tile* target = nullptr;
	Tile* target = FindNeighbour(dir);

	if (target->Walkable) MoveResultAction::MoveOk;
	if (!target->Walkable) MoveResultAction::Blocked;
	if (target == nullptr) MoveResultAction::LoadNewRoom;
	//else MoveResultAction::Undefined;

	return MoveResultAction();
}


void DungeonGame::MoveResult(MoveResultAction action, Direction dir)
{
	switch (action)
	{
	case MoveOk: MovePlayer(); break;
	case Blocked: break;
	case LoadNewRoom: LoadRoom(dir); break;
	default: Undefined;
	}
}


void DungeonGame::TryMove(Direction dir)
{
	MoveResultAction action;
	action = SetAction(dir);
	PlayerMovement(dir);
	MoveResult(action, dir);
}


void DungeonGame::TryMoveResult(MoveResult& result, Direction dir)
{
	switch (result.GetAction())
	{
	case MoveOk: PlayerMovement(dir); break;
	case Blocked: break;
	case LoadNewRoom: LoadRoom(dir); break;
	default: Undefined;
	}
}


void DungeonGame::Input(Direction dir)
{
	MoveResult result = TryMove(this->Hero, dir);
	TryMoveResult(result, dir);
}


MoveResult DungeonGame::TryMove(GameCharacter* character, Direction dir)
{
	MoveResult result;

	int x = character->PosX;
	int y = character->PosY;

	Tile* target = GetNeighbour(x, y, dir);
	result.tile = target;

	if (!target->Walkable)
	{
		result.action = MoveResultAction::Blocked;
		return result;
	}

	if (target == nullptr)
	{
		result.action = MoveResultAction::LoadNewRoom;
		return result;
	}

	result.action = MoveResultAction::MoveOk;
	return result;
}


void DungeonGame::PlayerMove(Direction dir)
{
	MoveResult result = TryMove(this->Hero, dir);

	switch (result.action)
	{
	case MoveResultAction::MoveOk:
		this->Hero->SetCurrentPos(result.tile->X, result.tile->Y, tileSizeX);
		this->Hero->CurrentTile = result.tile;
		break;

	case MoveResultAction::Blocked:
		break;

	case MoveResultAction::LoadNewRoom:
		int nextRoomX = CurrentRoomX;
		int nextRoomY = CurrentRoomY;

		switch (dir)
		{
		case North: nextRoomY = CurrentRoomY - 1; break;
		case East: nextRoomX = CurrentRoomX + 1; break;
		case South: nextRoomY = CurrentRoomY + 1; break;
		case West: nextRoomX = CurrentRoomX - 1; break;
		}

		if (nextRoomX < 0 || nextRoomX > NumRoomsX - 1 || nextRoomY < 0 || nextRoomY > NumRoomsY - 1) return;

		UpdateRoom(dir);
		LoadRoom(nextRoomX, nextRoomY);

		switch (dir)
		{
		case North: this->Hero->SetCurrentPos(this->Hero->PosX, RoomSize - 1, tileSizeX); break;
		case East:this->Hero->SetCurrentPos(0, this->Hero->PosY, tileSizeX); break;
		case South:this->Hero->SetCurrentPos(this->Hero->PosX, 0, tileSizeX); break;
		case West: this->Hero->SetCurrentPos(RoomSize - 1, this->Hero->PosY, tileSizeX); break;
		}

		this->Hero->CurrentTile = &Tiles[this->Hero->PosX][this->Hero->PosY];

		return;
		break;
	}
}


void DungeonGame::PlayerMove(Direction dir)
{
	Tile* current = this->Hero->CurrentTile;
	Tile* target = nullptr;

	switch (dir)
	{
	case North: target = current->NorthNeighbour; break;
	case East: target = current->EastNeightbour; break;
	case South: target = current->SouthNeighbour; break;
	case West: target = current->WestNeighbour; break;
	}

	if (target == nullptr)
	{
		int nextRoomX = CurrentRoomX;
		int nextRoomY = CurrentRoomY;

		switch (dir)
		{
		case North: nextRoomY = -1; break;
		case East: nextRoomX = 1; break;
		case South: nextRoomY = 1; break;
		case West: nextRoomX = -1; break;
		}

		LoadRoom(nextRoomX, nextRoomY);

		switch (dir)
		{
		case North: this->Hero->CurrentTile = &Tiles[current->X][RoomSize - 1]; break;
		case East: this->Hero->CurrentTile = &Tiles[0][current->Y]; break;
		case South: this->Hero->CurrentTile = &Tiles[current->X][0]; break;
		case West: this->Hero->CurrentTile = &Tiles[RoomSize - 1][current->Y]; break;
		}
		return;
	}

	if (target->Walkable)
	{
		this->Hero->CurrentTile = target;
	}
}

 
void DungeonGame::PlayerMove(Direction dir)
{
	MoveResult->TryMove(this->Hero->PosX, this->Hero->PosY, dir);

	if (MoveResult->GetAction() == MoveOk)
	{
		int posX = this->Hero->PosX;
		int posY = this->Hero->PosY;
		this->Hero->CurrentTile = &Tiles[posX][posY];

		int dirX = 0;
		int dirY = 0;

		switch (dir)
		{
		case North: dirY = -1; break;
		case East: dirX = 1; break;
		case South: dirY = 1; break;
		case West: dirX = -1; break;
		}

		int newX = this->Hero->PosX + dirX;
		int newY = this->Hero->PosY + dirY;
	}
}


void DungeonGame::PlayerMovement(Direction dir, int tile)
{
	switch (dir)
	{
	case North: this->Hero->Rect.y -= tile; break;
	case East: this->Hero->Rect.x += tile; break;
	case South: this->Hero->Rect.y += tile; break;
	case West: this->Hero->Rect.x -= tile; break;
	}
}


void DungeonGame::TryMove(int x, int y, GameCharacter* character, Tile* n, Direction dir)
{
	int x = character->PosX;
	int y = character->PosY;

	character->CurrentTile = &Tiles[x][y];

	n = GetNeighbour(x, y, dir);

	if (n->Walkable)
	{
		MoveResultAction::MoveOk;

		if (MoveResultAction::MoveOk)
	}



	void DungeonGame::SetTile()
{
	for (int x = 0; x < RoomSize; x++)
	{
		for (int y = 0; y < RoomSize; y++)
		{
			Tile* tile = &Tiles[x][y];
			Tile* heroTile = this->Hero->CurrentTile;
			if (tile->X == heroTile->X && tile->Y == heroTile->Y)
			{
				tile->HasHero = true;
				return;
			}
			else
			{
				tile->HasHero = false;
				return;
			}

			(tile == this->Enemy->CurrentTile) ? tile->HasEnemy = true : tile->HasEnemy = false;
		}
	}
}

bool DungeonGame::EnemyisAlive()
{
	if (this->Hero->PosX == this->Enemy->PosX && this->Hero->PosY == this->Enemy->PosY)
	{
		return false;
	}

	//else return true;


	//std::cout << EnemyisAlive() << std::endl;
}

}*/