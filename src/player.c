#include "player.h"

Player initPlayer(Coords c){
	Player p = {
		.coords=c, 
		.points=0, 
		.speed=2, 
		.direction=IDLE,
		.health=3
	} ;
	return p;
}

