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

// Tiles
#define TILE_WIDTH 40
#define TILE_HEIGHT TILE_WIDTH

// Board game
#define WIN_BOARD_WIDTH BOARD_WIDTH*TILE_WIDTH
#define WIN_BOARD_HEIGHT BOARD_HEIGHT*TILE_HEIGHT

// Score section (up)
#define WIN_SCORE_WIDTH WIN_BOARD_WIDTH
#define WIN_SCORE_HEIGHT 100

// Health section
#define WIN_HEALTH_WIDTH WIN_BOARD_WIDTH
#define WIN_HEALTH_HEIGHT TILE_HEIGHT

// Total window
#define WIN_WIDTH WIN_BOARD_WIDTH
#define WIN_HEIGHT WIN_BOARD_HEIGHT+WIN_SCORE_HEIGHT+WIN_HEALTH_HEIGHT

// space between health rendering
#define OFFSET 10

#define GUM_POINTS 10
#define GUM_SIZE 10
#define GUM_OFFSET (TILE_HEIGHT-GUM_SIZE)/2

#define BIGGUM_POINTS 50
#define BIGGUM_SIZE 20
#define BIGGUM_OFFSET (TILE_HEIGHT-BIGGUM_SIZE)/2

#define SUPER_TIME 10

#define GHOST_POINTS 200

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
    GATE = '6'
};

typedef enum LoadType LoadType;
enum LoadType
{
	NEW, RELOAD, CHANGE_LEVEL
};

Coords initCoords();
void print_Coords(Coords c);
Coords incrCoords(Coords coords, Direction dir, int speed);

bool collision(Coords coords1, int height1, int width1, Coords coords2, int height2, int width2);
// bool opositeDirection(Direction d1, Direction d2);
Direction opositeDirection(Direction dir);
void relativeRightLeftDir(Direction dir, Direction *relRight, Direction *relLeft);

#endif