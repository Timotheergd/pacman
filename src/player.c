#include "player.h"

Player initPlayer(Coords c){
	Player p = {.coords=c, .points=0, .speed=10, .direction=IDLE} ;
	return p;
}
