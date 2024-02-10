#include "ghost.h"

Ghost initGhost(Coords c){
	Ghost g = {
		.coords=c,
		.speed=3,
		.direction=IDLE,
		.death_time=time(NULL),
		.respawnPoint=c
	};
	return g;
}

GhostRespawn initGhostRespawn(Coords coords){
	GhostRespawn r = {coords};
	return r;
}