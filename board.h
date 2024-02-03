#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>




// Board size
#define BOARD_WIDTH 19
#define BOARD_HEIGHT 21

#define LEVEL_SIZE BOARD_WIDTH*BOARD_HEIGHT

#include "ressources.h"
#include "player.h"
#include "wall.h"
#include "ghost.h"
#include "warp.h"
#include "gum.h"

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
Board loadBoard(char (*level_content)[LEVEL_SIZE], Board *board);

#endif