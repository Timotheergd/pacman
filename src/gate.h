#ifndef GATE_H
#define GATE_H

#include "ressources.h"

/*
The player can never go through the gate
Ghosts can go throught if they are not killed less than GHOST_DEATH_TIME sec ago
*/

typedef struct Gate Gate;
struct Gate {
	Coords coords;
};
Gate initGate(Coords coords);

#include "board.h"

#endif