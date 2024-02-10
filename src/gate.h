#ifndef GATE_H
#define GATE_H

#include "ressources.h"

typedef struct Gate Gate;
struct Gate {
	Coords coords;
};
Gate initGate(Coords coords);

#include "board.h"

#endif