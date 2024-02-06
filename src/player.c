#include "player.h"

Player initPlayer(Coords c){
	Player p = {
		.coords=c, 
		.points=0, 
		.speed=4, 
		.direction=IDLE,
		.health=3
	} ;
	return p;
}

