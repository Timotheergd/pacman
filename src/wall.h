#ifndef WALL_H
#define WALL_H

#include "ressources.h"

typedef struct Wall Wall;
struct Wall {
	Coords coords;
};
Wall initWall(Coords coords);

#include "board.h"

#endif