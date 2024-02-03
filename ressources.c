#include "ressources.h"

Coords initCoords(int i, int j){
	Coords coords = {i,j};
	return coords;
}

void print_Coords(Coords c){
    printf("c.x=%d, c.y=%d\n", c.x, c.y);
}