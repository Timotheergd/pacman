#include "ressources.h"

Coords initCoords(int i, int j){
	Coords coords = {i,j};
	return coords;
}

void print_Coords(Coords c){
    printf("c.x=%d, c.y=%d\n", c.x, c.y);
}

Coords incrCoords(Coords coords, Direction dir, int speed){
	switch(dir){
		case UP:
			coords.y-=speed;
			break;
		case DOWN:
			coords.y+=speed;
			break;
		case RIGHT:
			coords.x+=speed;
			break;
		case LEFT:
			coords.x-=speed;
			break;
	}
	// check boundaries
	coords.x%=WIN_WIDTH-TILE_WIDTH;															// right
	if(coords.y>(WIN_SCORE_HEIGHT+WIN_BOARD_HEIGHT-TILE_WIDTH)) coords.y=WIN_SCORE_HEIGHT;	// down
	if(coords.x<0) coords.x=WIN_WIDTH-TILE_WIDTH;											// left
	if(coords.y<WIN_SCORE_HEIGHT) coords.y=WIN_SCORE_HEIGHT+WIN_BOARD_HEIGHT-TILE_HEIGHT;	// up

	return coords;
}

bool collision(Coords coords1, int height1, int width1, Coords coords2, int height2, int width2){
    // Can be optimised
    return ((coords2.x+1 > coords1.x && coords2.x+1 < coords1.x+width1) && (coords2.y+1 > coords1.y && coords2.y+1 < coords1.y+height1)) || 					// left up corner
            ((coords2.x+width2-1 > coords1.x && coords2.x+width2-1 < coords1.x+width1) && (coords2.y+1 > coords1.y && coords2.y+1 < coords1.y+height1)) || 		// right up corner
            ((coords2.x+1 > coords1.x && coords2.x+1 < coords1.x+width1) && (coords2.y+height2-1 > coords1.y && coords2.y+height2-1 < coords1.y+height1)) || 	// left down corner
            ((coords2.x+width2-1 > coords1.x && coords2.x+width2-1 < coords1.x+width1) && (coords2.y+height2-1 > coords1.y && coords2.y+height2-1 < coords1.y+height1)); // right down corner
}

// Return true if 
Direction opositeDirection(Direction dir){
	// is opposite direction ??? return (d1==RIGHT && d2==LEFT) || (d1==LEFT && d2==RIGHT) || (d1==UP && d2==DOWN) || (d1==DOWN && d2==UP);
	switch(dir){
		case UP:
			return DOWN;
			break;
		case RIGHT:
			return LEFT;
			break;
		case DOWN:
			return UP;
			break;
		case LEFT:
			return RIGHT;
			break;
		default:
			return IDLE;
			break;
	}
}

void relativeRightLeftDir(Direction dir, Direction *relRight, Direction *relLeft){
	switch(dir){
		case UP:
			*relRight=RIGHT;
			*relLeft=LEFT;
			break;
		case RIGHT:
			*relRight=DOWN;
			*relLeft=UP;
			break;
		case DOWN:
			*relRight=LEFT;
			*relLeft=RIGHT;
			break;
		case LEFT:
			*relRight=UP;
			*relLeft=DOWN;
			break;
	}
}