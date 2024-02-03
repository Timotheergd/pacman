#ifndef GUM_H
#define GUM_H

#include "ressources.h"

typedef struct Gum Gum;
struct Gum {
	Coords coords;
};

typedef struct BigGum BigGum;
struct BigGum {
	Coords coords;
};

#include "board.h"

Gum initGum(Coords c);
BigGum initBigGum(Coords c);

#endif