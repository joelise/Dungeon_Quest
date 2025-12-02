#include "DungeonGame.h"



DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{
	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
	
	srand(time(NULL));
}

DungeonGame::~DungeonGame()
{
	delete this->Hero;
}

void DungeonGame::LoadTextures(SDL_Renderer* renderer)
{
	this->Hero = new Player;
	this->Hero->Texture = IMG_LoadTexture(renderer, path_Hero.c_str());
	SDL_SetTextureScaleMode(this->Hero->Texture, SDL_SCALEMODE_NEAREST);
	//this->Hero->SetCurrentPos(spawnPosX, spawnPosY, tileSizeX);
	//this->Hero->Rect.x = 5;
	//this->Hero->Rect.y = 5;
	
	//this->Hero->Rect.w = tileSizeX;
	//this->Hero->Rect.h = tileSizeY;

	
	//this->carpets = IMG_LoadTexture(renderer, path_Carpet->c_str());
	//this->tile = new Tile;
	//this->tile->texture = IMG_LoadTexture(renderer, path_Carpet->c_str());
	//this->tile->Rect.x = 0;
	//this->tile->Rect.y = 0;
	//this->tile->Rect.w = tileSizeX;
	//this->tile->Rect.h = tileSizeY;

	//int textureLength = 0;
	
	//Tiles[0][0] = new Tile;
	//SDL_Texture* CarpetTexture
	//this->Tiles[9][9].texture = IMG_LoadTexture(renderer, path_Carpet->c_str());
	//this->Tiles[9][9].Rect.x = 0;
	//this->Tiles[9][9].Rect.y = 0;
	//this->Tiles[9][9].Rect.w = tileSizeX;
	//this->Tiles[9][9].Rect.h = tileSizeY;

	for (int i = 0; i < TextureAmount; i++)
	{
		
		CarpetSurf = SDL_LoadBMP(path_Carpet[i].c_str());
		Carpets[i] = SDL_CreateTextureFromSurface(renderer, CarpetSurf);
		SDL_SetTextureScaleMode(Carpets[i], SDL_SCALEMODE_NEAREST);
		SDL_DestroySurface(CarpetSurf);
	}
	

	
	
}

int DungeonGame::RandomNum()
{
	return rand() % RoomTypes;
}

void DungeonGame::RandomizeDungeon()
{
	for (int x = 0; x < NumRoomsX; x++)
	{
		for (int y = 0; y < NumRoomsY; y++)
		{
			DungeonLayout[x][y] = RandomNum();
			
		}
	}

	for (int x = 0; x < NumRoomsX; x++)
	{
		for (int y = 0; y < NumRoomsY; y++)
		{
			std::cout << DungeonLayout[x][y] << " ";
		}
	}

}

void DungeonGame::RandomRoom()
{
	CurrentRoomX = rand() % NumRoomsX;
	CurrentRoomY = rand() % NumRoomsY;

	std::cout << "Starting in Random Room ( " << CurrentRoomX << ", " << CurrentRoomY << ")" << std::endl;
}

Tile* DungeonGame::GetNeighbour(int currentX, int currentY, Direction dir)
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
}

void DungeonGame::SetNeighbour()
{
	for (int x = 0; x < RoomSize; x++)
	{
		for (int y = 0; y < RoomSize; y++)
		{
			Tile& tile = Tiles[x][y];
			
			// North
			(y == 0) ? tile.NorthNeighbour = nullptr : tile.NorthNeighbour = &Tiles[x][y - 1];
			
			// East
			(x == RoomSize - 1) ? tile.EastNeightbour = nullptr : tile.EastNeightbour = &Tiles[x + 1][y];

			// South
			(y == RoomSize - 1) ? tile.SouthNeighbour = nullptr : tile.SouthNeighbour = &Tiles[x][y + 1];

			// West
			(x == 0) ? tile.WestNeighbour = nullptr : tile.WestNeighbour = &Tiles[x - 1][y];
		}
	}

}





void DungeonGame::LoadRoom(const char* file)
{
	//std::cout << "LoadRoom started for file:" << file << std::endl;
	for (int x = 0; x < RoomSize; x++)
	{
		for (int y = 0; y < RoomSize; y++)
		{
			//std::cout << "Reseting tile x=" << x << "y=" << y << std::endl;
			this->Tiles[x][y] = Tile();
		}
	}
	SDL_Surface* surface = SDL_LoadBMP(file);
	
	
	const SDL_PixelFormatDetails* pixelDetails = SDL_GetPixelFormatDetails(surface->format);
	const Uint8 bpp = SDL_BYTESPERPIXEL(surface->format);
	SDL_Color col;
	
	//SDL_Texture* carpet[] = Carpets[TextureAmount];
	
	for (int y = 0; y < surface->h; y++) 
	{
		for (int x = 0; x < surface->w; x++) 
		{
			//if (x >= RoomSize || y >= RoomSize)
			//{
				//std::cout << "skipping out of bounds tile x=" << x << "y=" << y << std::endl;
				//continue;
			//}
			Uint8* pixel = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bpp;
			SDL_GetRGB(*reinterpret_cast<Uint32*>(pixel), pixelDetails, NULL, &col.r, &col.g, &col.b);
			
			//std::cout << "configuring tile x=" << x << " y=" << y << " color=( " << (int)col.r << ", " << (int)col.g << ", " << (int)col.b << ")" << std::endl;
			
			this->Tiles[x][y].Configure(col, x * tileSizeX, y * tileSizeY, tileSizeX, Carpets);
			//this->Tiles[x][y].X = x;
			//this->Tiles[x][y].Y = y;

			
			//SetNeighbour();

			//this->Tiles[x][y].Configure(col, tile->Rect.x, tile->Rect.y, tileSizeX, carpet);
			// Col now contains pixel colour at position x,y
			// Now configure the tile at x, y with col
			//this->Tiles[x][y].Configure(col, x, y, tileSizeX, tileSizeY)
			//this->Hero->Rect.x = spawnPosX;
			//this->Hero->Rect.y = spawnPosY;
		}
	}
	SDL_DestroySurface(surface);
}

void DungeonGame::LoadRoom(int x, int y)
{
	int index = DungeonLayout[x][y];
	const char* fileName = RoomFiles[index];

	LoadRoom(fileName);
}

bool DungeonGame::FirstWalkable(int& posX, int& posY)
{
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
	return false;
}

void DungeonGame::SetPlayerPos()
{
	if (FirstWalkable(spawnPosX, spawnPosY))
	{
		this->Hero->SetCurrentPos(spawnPosX, spawnPosY, tileSizeX);
		this->Hero->CurrentTile = &Tiles[spawnPosX][spawnPosY];
	}
}

void DungeonGame::UpdateRoom(Direction dir)
{
	switch (dir)
	{
	case North: CurrentRoomY--; break;
	case East: CurrentRoomX++; break;
	case South: CurrentRoomY++; break;
	case West: CurrentRoomX--; break;
	}


}

void DungeonGame::PlayerMove(Direction dir)
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

	//this->Hero->CurrentTile = &Tiles[newX][newY];
	Tile* target = nullptr;
	Tile* current = this->Hero->CurrentTile;
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
		case North: nextRoomY = CurrentRoomY - 1; break;
		case East: nextRoomX = CurrentRoomX + 1; break;
		case South: nextRoomY = CurrentRoomY + 1; break;
		case West: nextRoomX = CurrentRoomX - 1; break;
		}

		
		UpdateRoom(dir);
		LoadRoom(nextRoomX, nextRoomY);

		switch (dir)
		{
		case North: this->Hero->SetCurrentPos(posX, RoomSize - 1, tileSizeX); break;
		case East:this->Hero->SetCurrentPos(0, posY, tileSizeX); break;
		case South:this->Hero->SetCurrentPos(posX, 0, tileSizeX); break;
		case West: this->Hero->SetCurrentPos(RoomSize - 1, posY, tileSizeX); break;
		}
		
		this->Hero->CurrentTile = &Tiles[this->Hero->PosX][this->Hero->PosY];
		/*switch (dir)
		{
		case North: this->Hero->CurrentTile = &Tiles[current->X][RoomSize - 1]; break;
		case East:this->Hero->CurrentTile = &Tiles[0][current->Y]; break;
		case South:this->Hero->CurrentTile = &Tiles[current->X][0]; break;
		case West: this->Hero->CurrentTile = &Tiles[RoomSize - 1][current->Y]; break;
		}*/
		//this->Hero->CurrentTile = &Tiles[newX][newY];
		//this->Hero->SetCurrentPos(newX, newY, tileSizeX);
		//current = &Tiles[newX][newY];
		//this->Hero->CurrentTile = current;
		return;
	}

	if (target->Walkable)
	{
		//this->Hero->CurrentTile = target;
		//this->Hero->CurrentTile = &Tiles[target->X][target->Y];
		//this->Hero->CurrentTile = target;
		//this->Hero->SetCurrentPos(target->X, target->Y, tileSizeX);
		//current = target;
		this->Hero->SetCurrentPos(newX, newY, tileSizeX);
		this->Hero->CurrentTile = &Tiles[newX][newY];
		//current = &Tiles[newX][newY];
		//this->Hero->CurrentTile = current;
		//current = target;
		//target = &Tiles[newX][newY];
	}
		//return;
	




	//this->Hero->SetCurrentPos(newX, newY, tileSizeX);
	//current = &Tiles[newX][newY];

	
}

/*void DungeonGame::PlayerMove(Direction dir)
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
}*/



/*void DungeonGame::PlayerMove(Direction dir)
{
	//Hero->GetCurrentPos(Hero, PlayerPosX, PlayerPosY, tileSizeX);
	Hero->MovePlayer(dir, this->Hero, tileSizeX);
	
	
}*/

/*void DungeonGame::PlayerMovement(Direction dir, int tile)
{
	switch (dir)
	{
	case North: this->Hero->Rect.y -= tile; break;
	case East: this->Hero->Rect.x += tile; break;
	case South: this->Hero->Rect.y += tile; break;
	case West: this->Hero->Rect.x -= tile; break;
	}
}*/

void DungeonGame::Update(double)
{
	
}



void DungeonGame::test()
{

	int posx = this->Hero->PosX;
	int posy = this->Hero->PosY;
	int nposx;
	int nposy;

	std::cout << posx << posy << std::endl;
	Tile& tile = Tiles[posx][posy];
	//tile.NorthNeighbour = GetNeighbour(posx, posy, North);
	//std::cout << tile.NorthNeighbour << std::endl;
	//std::cout << tile.NorthNeighbour->X << ", " << tile.NorthNeighbour->Y << std::endl;
	//std::cout << tile.EastNeightbour->X << ", " << tile.EastNeightbour->Y << std::endl;

}

void DungeonGame::StartGame(SDL_Renderer* renderer)
{
	RandomizeDungeon();
	RandomRoom();
	LoadRoom(CurrentRoomX, CurrentRoomY);
	SetNeighbour();
	LoadTextures(renderer);
	SetPlayerPos();
}










