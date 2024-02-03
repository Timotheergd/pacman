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
// #include "src/warp.h" // Waiting for a solution...
#include "src/gum.h"

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

	/// ********** SDL INIT **********
	initSDL();
	SDL_Window* win = createWindow("PACMAN", WIN_WIDTH, WIN_HEIGHT);
	SDL_Renderer* rend = createRenderer(win);

	// Load textures
	SDL_Texture* player_tex = loadTexture("/home/timothee/kDrive/Programmation/C/L2/pacman_ressources/texture/pacman-art/pacman-right/1.png", rend);
	
	renderTexture(player_tex, rend, 100, 100, TILE_WIDTH, TILE_HEIGHT);

	updateDisplay(rend);

	SDL_Delay(3000);

	return 0;
}