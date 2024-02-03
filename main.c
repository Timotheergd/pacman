#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "ressources.h"
#include "board.h"
#include "graphics.h"
#include "wall.h"
#include "player.h"
#include "ghost.h"
// #include "warp.h" // Waiting for a solution...
#include "gum.h"

// #define WIN_WIDTH 800
// #define WIN_HEIGHT 800
// #define FPS 60

const int NBDEPMAX = 30;

int main(int argc, char *argv[]){

	char level_file[50]="levels.txt";
	char level_content[LEVEL_SIZE]="";
	int level_number=3;

	// init board
	Board board=initBoard();
	read_level(level_file, level_number, &level_content);
	loadBoard(&level_content, &board);
	
	printf("level %d:%s\n",level_number, level_content);

	printBoardContent(&board);

	return 0;
}