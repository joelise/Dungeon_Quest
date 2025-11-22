#include "DungeonGame.h"



DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{
	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
	
	
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
	this->Hero->GetCurrentPos(spawnPosX, spawnPosY, tileSizeX);
	//this->Hero->Rect.x = 5;
	//this->Hero->Rect.y = 5;
	
	//this->Hero->Rect.w = tileSizeX;
	//this->Hero->Rect.h = tileSizeY;

	
	//this->carpets = IMG_LoadTexture(renderer, path_Carpet->c_str());
	this->tile = new Tile;
	this->tile->texture = IMG_LoadTexture(renderer, path_Carpet->c_str());
	this->tile->Rect.x = 0;
	this->tile->Rect.y = 0;
	this->tile->Rect.w = tileSizeX;
	this->tile->Rect.h = tileSizeY;

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




void DungeonGame::LoadRoom(const char* file)
{
	SDL_Surface* surface = SDL_LoadBMP(file);
	
	const SDL_PixelFormatDetails* pixelDetails = SDL_GetPixelFormatDetails(surface->format);
	const Uint8 bpp = SDL_BYTESPERPIXEL(surface->format);
	SDL_Color col;
	
	//SDL_Texture* carpet[] = Carpets[TextureAmount];
	
	for (int y = 0; y < surface->h; y++) 
	{
		for (int x = 0; x < surface->w; x++) 
		{
			Uint8* pixel = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bpp;
			SDL_GetRGB(*reinterpret_cast<Uint32*>(pixel), pixelDetails, NULL, &col.r, &col.g, &col.b);
			
			
			this->Tiles[x][y].Configure(col, x * tileSizeX, y * tileSizeY, tileSizeX, Carpets);
			SDL_DestroySurface(surface);
			//this->Tiles[x][y].Configure(col, tile->Rect.x, tile->Rect.y, tileSizeX, carpet);
			// Col now contains pixel colour at position x,y
			// Now configure the tile at x, y with col
			//this->Tiles[x][y].Configure(col, x, y, tileSizeX, tileSizeY)
			//this->Hero->Rect.x = spawnPosX;
			//this->Hero->Rect.y = spawnPosY;
		}
	}
}

void DungeonGame::PlayerMove(Direction dir)
{
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

	if (!Tiles[newX][newY].Walkable)
	{
		return;
	}

	this->Hero->GetCurrentPos(newX, newY, tileSizeX);
}

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







