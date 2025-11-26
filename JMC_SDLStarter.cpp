
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "DungeonGame.h"
#include "Player.h"
#include "Enums.h"

using namespace std;

const int resX = 1027;
const int resY = 768;
const int GridSizeX = 10;
const int GridSizeY = 10;
const float TileSize = resY / GridSizeX;

// Global tile sizes
static const int TileWidth = resX / 10;
static const int TileHeight = resY / 10;
// Hero rect
//static SDL_FRect heroRect{ 0, 0, TileWidth, TileHeight };

 /* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;

static const char* ProjectName = "JMC Starter Project";
const static char* Room = { "Data/Rooms/Room04.bmp" };
static DungeonGame* Game;
static Player* player;
static Direction* dir;
static Tile* tile;

static Uint64 now;
static Uint64 last;




/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{     
    SDL_SetAppMetadata(ProjectName, "1.0", "");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(ProjectName, resX, resY, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    Game = new DungeonGame(TileSize, TileSize);
    
    if (Game == nullptr)
    {
        cout << "Null";
    }
    Game->RandomizeDungeon();
    
   Game->LoadRoom(TileSize, TileSize);
   Game->SetNeighbour();
    Game->LoadTextures(renderer);
   
    
    Game->SetPlayerPos();
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        // keyboard events    
        if (event->key.scancode == SDL_SCANCODE_W)
        {
            //Game->PlayerMovement(North, TileSize);
            Game->PlayerMove(North);
            Game->test();
        }
        if (event->key.scancode == SDL_SCANCODE_S)
        {
            //Game->PlayerMovement(South, TileSize);
            Game->PlayerMove(South);
            Game->test();
        }
        if (event->key.scancode == SDL_SCANCODE_A)
        {
            //Game->PlayerMovement(West, TileSize);
            Game->PlayerMove(West);
            Game->test();
        }
        if (event->key.scancode == SDL_SCANCODE_D)
        {
            //Game->PlayerMovement(East, TileSize);
            Game->PlayerMove(East);
            Game->test();
        }

    }

    
    

    return SDL_APP_CONTINUE;  /* carry on with the program! */
    
}

/*  This function runs once per frame, and is the heart of the program.
    Think of this like Unity's Update() loop */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    last = now;
    now = SDL_GetPerformanceCounter();
    double deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());
    Game->Update(deltaTime);

    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);  /* dark gray, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    // Your Update code goes here.
    
    

    // Draw the tiles/grid
    
    for (int x = 0; x < GridSizeX; x++)
    {
        for (int y = 0; y < GridSizeY; y++)
        {
            
            SDL_RenderTexture(renderer, Game->Tiles[x][y].texture, NULL, &Game->Tiles[x][y].Rect);
            //SDL_RenderTexture(renderer, Game->tile->texture, NULL, &Game->tile->Rect);
            //SDL_RenderTexture(renderer, Game->Tiles[x][y].texture, NULL, &Game->Tiles[x][y].Rect);
        }
    }

    // Render the hero
    SDL_RenderTexture(renderer, Game->Hero->Texture, NULL, &Game->Hero->Rect);
   Game->LoadRoom(TileSize, TileSize);
    Game->SetNeighbour();
    
   // SDL_RenderTexture(renderer, Game->tile->texture, NULL, &Game->tile->Rect);
    //
    SDL_RenderPresent(renderer);  /* put it all on the screen! */

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{    
    delete Game;
    /* SDL will clean up the window/renderer for us. */
}

