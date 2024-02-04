#ifndef PLAYER_H
#define PLAYER_H

#include "ressources.h"

typedef struct Player Player;
struct Player {
	 Coords coords;
	 int points;
	 int speed;
	 Direction direction;
};


#include "board.h"

Player initPlayer(Coords c);


#endif