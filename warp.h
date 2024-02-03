#ifndef WARP_H
#define WARP_H

#include "ressources.h"

/*
TODO : Find a way to store the coords and the destination of the warp in the same time
For now, I cannot use this object :(
*/

/*
The warp teleport an object to an other place of the board.
It is placed on a tile but the hitbox is small an on the side
so the object can travel on the bock an teleport only if it goes to the end
*/
typedef struct Warp Warp;
struct Warp {
	Coords coords;
	Coords destination;
	Direction direction; // on which side of the tile it is 
};
Warp initWarp(Coords coords, Coords dest);

#include "board.h"

#endif