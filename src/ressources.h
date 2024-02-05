#ifndef RESSOURCES_H
#define RESSOURCES_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// Constants

// Board size
#define BOARD_WIDTH 19
#define BOARD_HEIGHT 21

#define LEVEL_SIZE BOARD_WIDTH*BOARD_HEIGHT

// SDL Window size
#define WIN_WIDTH 19*40
#define WIN_HEIGHT 21*40
#define TILE_WIDTH WIN_WIDTH/BOARD_WIDTH
#define TILE_HEIGHT WIN_HEIGHT/BOARD_HEIGHT

#define FPS 60

// Additional Structs / Enums

typedef struct Coords Coords;
struct Coords {
	int x;
	int y;
};

typedef enum Direction Direction;
enum Direction
{
	RIGHT, LEFT, UP, DOWN, IDLE
};

typedef enum Entity Entity;
enum {
    WALL = '1',
    PLAYER = '2',
    GHOST = '3',
    GUM = '4',
    BIGGUM = '5',
    WARP = '6'
};

Coords initCoords();
void print_Coords(Coords c);
Coords incrCoords(Coords coords, Direction dir, int speed);

bool collision(Coords coords1, int height1, int width1, Coords coords2, int height2, int width2);
// bool opositeDirection(Direction d1, Direction d2);
Direction opositeDirection(Direction dir);
void relativeRightLeftDir(Direction dir, Direction *relRight, Direction *relLeft);

#endif