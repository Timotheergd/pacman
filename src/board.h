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

// store the player and an array of each type of objects with they size
typedef struct Board Board;
struct Board {
	Player player;
	Wall *wall_list;
	Ghost *ghost_list;
	Warp *warp_list;
	Gum *gum_list;
	BigGum *bigGum_list;
    int nbWall;
    int nbGhost;
    int nbWarp;
    int nbGum;
    int nbBigGum;
};

void read_level(char filename[], int level_number, char (*level_content)[]);

Board initBoard();
void printBoardContent(Board *board);
Board loadBoard(char (*level_content)[LEVEL_SIZE], Board *board, bool first_load);

// SDL
void renderWalls(Board *board, SDL_Texture *tex, SDL_Renderer *rend);
bool wallCollision(Coords coords, Board *board);
bool ghostCollision(Coords coords, Board *board);


bool movePlayer(Board *board, Direction direction);
void moveGhosts(Board *board);

void renderGhosts(Board *board, SDL_Texture *tex, SDL_Renderer *rend);

void renderPlayerHealth(Board *board, SDL_Texture *tex, SDL_Renderer *rend);

void renderGum(Board *board, SDL_Texture *tex, SDL_Renderer *rend);
bool eatGum(Board *board);

void renderPoints(Board *board, TTF_Font* font, SDL_Color color, SDL_Renderer *rend);

#endif