#ifndef GHOST_H
#define GHOST_H

#include "ressources.h"
#include "time.h"

typedef struct Ghost Ghost;
struct Ghost {
	Coords coords;
	int speed;
	Direction direction;
	time_t death_time;
	Coords respawnPoint;
	time_t vulnerable_time;
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