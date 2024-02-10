#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ressources.h"
#include "player.h"
#include "wall.h"
#include "ghost.h"
#include "warp.h"
#include "gum.h"
#include "gestionGraphique.h"
#include "gate.h"

// store every objects of the map
typedef struct Board Board;
struct Board {
	Player player;
	Wall *wall_list;
	Ghost *ghost_list;
	Warp *warp_list;
	Gum *gum_list;
	BigGum *bigGum_list;
	Gate *gate_list;
	GhostRespawn *ghostRespawn_list;
    int nbWall;
    int nbGhost;
    int nbWarp;
    int nbGum;
    int nbBigGum;
	int nbGate;
	int nbGhostRespawn;
};

void read_level(char filename[], int level_number, char (*level_content)[]);

Board initBoard();
void printBoardContent(Board *board); // for debugging
Board loadBoard(char (*level_content)[LEVEL_SIZE], Board *board, LoadType load_type);

// SDL
void renderWalls(Board *board, SDL_Texture *tex, SDL_Renderer *rend);
bool wallCollision(Coords coords, Board *board);
bool gateCollision(Coords coords, Board *board);
int ghostCollision(Coords coords, Board *board);

bool movePlayer(Board *board, Direction direction);
void moveGhosts(Board *board);

void renderGhosts(Board *board, SDL_Texture *tex, SDL_Renderer *rend);

void renderPlayerHealth(Board *board, SDL_Texture *tex, SDL_Renderer *rend);

void renderGum(Board *board, SDL_Texture *tex, SDL_Renderer *rend);
bool eatGum(Board *board);

void renderPoints(Board *board, TTF_Font* font, SDL_Color color, SDL_Renderer *rend);

void renderBigGum(Board *board, SDL_Texture *tex, SDL_Renderer *rend);

bool eatBigGum(Board *board, time_t *super_mode);

void renderGate(Board *board, SDL_Texture *tex, SDL_Renderer *rend);

#endif