#ifndef RESSOURCES_H
#define RESSOURCES_H

#include <string.h>
#include <stdio.h>

// Coords
typedef struct Coords Coords;
struct Coords {
	int x;
	int y;
};

Coords initCoords();
void print_Coords(Coords c);

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

#endif