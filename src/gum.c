#include "gum.h"

Gum initGum(Coords c){
	Gum p = {.coords=c};
	return p;
}

BigGum initBigGum(Coords c){
	BigGum p = {.coords=c};
	return p;
}