#include "ghost.h"

Ghost initGhost(Coords c){
	Ghost g = {
		.coords=c,
		.speed=3,
		.direction=IDLE
	};
	return g;
}