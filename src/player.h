#ifndef PLAYER_H
#define PLAYER_H

#include "ressources.h"
#include "time.h"

typedef struct Player Player;
struct Player {
	Coords coords;
	int points;
	int speed;
	Direction direction;
	int health;
	int streak;
};


#include "board.h"

Player initPlayer(Coords c);


#endif