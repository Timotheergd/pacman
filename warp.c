#include "warp.h"

Warp initWarp(Coords coords, Coords dest){
	Warp w = {coords, dest} ;
	return w;
}