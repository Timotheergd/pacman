#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ressources.h"
#include "player.h"
#include "wall.h"
#include "ghost.h"
#include "gum.h"
#include "gestionGraphique.h"
#include "gate.h"

// store every objects of the map
typedef struct Board Board;
struct Board {
	Player player;
	Wall *wall_list;
	Ghost *ghost_list;
	Gum *gum_list;
	BigGum *bigGum_list;
	Gate *gate_list;
	GhostRespawn *ghostRespawn_list;
    int nbWall;
    int nbGhost;
    int nbGum;
    int nbBigGum;
	int nbGate;
	int nbGhostRespawn;
};

void read_level(char filename[], int level_number, char (*level_content)[]);

// Board
Board initBoard();
void printBoardContent(Board *board); // for debugging
Board loadBoard(char (*level_content)[LEVEL_SIZE], Board *board, LoadType load_type);
void freeBoard(Board *board);

// Collisions
bool wallCollision(Coords coords, Board *board);
bool gateCollision(Coords coords, Board *board);
int ghostCollision(Coords coords, Board *board);

// Move
bool movePlayer(Board *board, Direction direction);
void moveGhosts(Board *board);

// Actions
void updatePlayerStreak(Board *board);
void allGhostIncrSpeed(Board *board, int speed_incr);
void eatGhost(Board *board, int collidedGhost);
bool eatGum(Board *board);
bool eatBigGum(Board *board);

// Render
void renderPlayerDeath(Board *board, SDL_Texture* (*player_death_tex)[PLAYER_NB_DEATH_TEXTURE_ANIMATION], SDL_Texture *blank_tex, SDL_Renderer *rend);
void renderWalls(Board *board, SDL_Texture *tex, SDL_Renderer *rend);
void renderGum(Board *board, SDL_Texture *tex, SDL_Renderer *rend);
void renderBigGum(Board *board, SDL_Texture *tex, SDL_Renderer *rend);
void renderPlayer(Board *board, SDL_Texture (*(*player_tex)[][PLAYER_NB_TEXTURES_PER_DIRECTION_ANIMATION]), SDL_Renderer *rend, int nb_usec_since_launch);
void renderGhosts(Board *board, SDL_Texture (*(*tex)[][5]), SDL_Renderer *rend, int nb_usec_since_launch);
void renderPlayerHealth(Board *board, SDL_Texture *tex, SDL_Renderer *rend);
void renderPoints(Board *board, TTF_Font* font, SDL_Color color, SDL_Renderer *rend);
void renderLevel(Board *board, TTF_Font* font, SDL_Color color, SDL_Renderer *rend, int level);
void renderGate(Board *board, SDL_Texture *tex, SDL_Renderer *rend);

#endif