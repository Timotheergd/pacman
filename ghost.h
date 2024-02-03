#ifndef GHOST_H
#define GHOST_H

#include "ressources.h"

typedef struct Ghost Ghost;
struct Ghost {
	Coords coords;
	int speed;
};
Ghost initGhost();

#include "board.h"

#endif