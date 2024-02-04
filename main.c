#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "src/ressources.h"
#include "src/board.h"
#include "src/gestionGraphique.h"
#include "src/wall.h"
#include "src/player.h"
#include "src/ghost.h"
// #include "srwarp.h" // Waiting for a solution...
#include "src/gum.h"

int main(int argc, char *argv[]){

	/// ********** BOARD INIT **********
	// read file
	char level_file[50]="levels.txt";
	char level_content[LEVEL_SIZE]="";
	int level_number=6;
	read_level(level_file, level_number, &level_content);
	
	// init board
	Board board=initBoard();
	loadBoard(&level_content, &board);
	
	// TEST
	printf("level %d:%s\n",level_number, level_content);
	printBoardContent(&board);

	/// ********** SDL INIT **********
	initSDL();
	SDL_Window* win = createWindow("PACMAN", WIN_WIDTH, WIN_HEIGHT);
	SDL_Renderer* rend = createRenderer(win);

	// Load textures
	SDL_Texture* player_tex = loadTexture("assets/textures/pacman/pacman_right_open.png", rend);
	SDL_Texture* wall_tex = loadTexture("assets/textures/wall.png", rend);

	// ********** GAME VARIABLES **********

	Direction direction = IDLE;


	bool close = false;
	while(!close){
		SDL_Event event;
		// Get keys / direction
		processKeyboard(&close, &direction);

		// Move

		//clear renderer
		clearRenderer(rend);

		//render objects
		renderWalls(&board, wall_tex, rend);
		renderTexture(player_tex, rend, TILE_WIDTH*9, TILE_HEIGHT*15, TILE_WIDTH, TILE_HEIGHT);

		// update display
		updateDisplay(rend);
	}
	

	// SDL_Delay(3000);

	QuitSDL(win, rend);

	return 0;
}