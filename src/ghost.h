#ifndef GHOST_H
#define GHOST_H

#include "ressources.h"

typedef struct Ghost Ghost;
struct Ghost {
	Coords coords;
	int speed;
	Direction direction;
	int death_time;
	Coords respawnPoint;
};
Ghost initGhost();


/*
	Create a respawn point and a ghost
*/
typedef struct GhostRespawn GhostRespawn;
struct GhostRespawn {
	Coords coords;
};
GhostRespawn initGhostRespawn();

#include "board.h"

#endif