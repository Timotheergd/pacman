#include "player.h"

Player initPlayer(Coords c){
	Player p = {.coords=c, .points=0, .speed=3, .direction=IDLE} ;
	return p;
}

