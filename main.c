#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "src/ressources.h"
#include "src/board.h"
#include "src/gestionGraphique.h"
#include "src/wall.h"
#include "src/player.h"
#include "src/ghost.h"
#include "src/gate.h"
// #include "warp.h" // Waiting for a solution...
#include "src/gum.h"

int main(int argc, char *argv[]){

	/// ********** BOARD INIT **********
	// read file
	char level_file[50]="levels.txt";
	char level_content[LEVEL_SIZE]="";
	int level_number=7;
	read_level(level_file, level_number, &level_content);
	
	// init board
	Board board=initBoard();
	LoadType load_type=NEW;
	loadBoard(&level_content, &board, load_type);
	load_type=RELOAD;
	
	// TEST
	printf("level %d:%s\n",level_number, level_content);
	// printBoardContent(&board);

	/// ********** SDL INIT **********
	initSDL();
	SDL_Window* win = createWindow("PACMAN", WIN_WIDTH, WIN_HEIGHT);
	SDL_Renderer* rend = createRenderer(win);

	// Load textures
	SDL_Texture* player_tex = loadTexture("assets/textures/pacman/pacman_right_open.png", rend);
	SDL_Texture* wall_tex = loadTexture("assets/textures/wall.png", rend);
	SDL_Texture* ghost_tex = loadTexture("assets/textures/ghost/ghost_red_right.png", rend);
	SDL_Texture* ghost_scared_tex = loadTexture("assets/textures/ghost/ghost_blue_right.png", rend);
	SDL_Texture* gum_tex = loadTexture("assets/textures/gum/gum.png", rend);
	SDL_Texture* biggum_tex = loadTexture("assets/textures/gum/biggum.png", rend);
	SDL_Texture* gate_tex = loadTexture("assets/textures/red_gate.png", rend);

	// *********** FONTS **********
	TTF_Init();
	SDL_Color White = {255, 255, 255};
	TTF_Font* points_font = loadFont("assets/Fonts/emulogic.ttf", 10);
	
	// ********** GAME VARIABLES **********
	Direction key_direction = IDLE;
	bool close = false;
	bool on_level = true;
	time_t super_mode;

	// ***** TEMP VAR / QUICK TESTS ******
	int i=0;

	while(!close){
		SDL_Event event;

		printf("HERE WE GO AGAIN !\n");
	
		// Reset values
		on_level=true;
		loadBoard(&level_content, &board, load_type);
		load_type=RELOAD;
		super_mode = time(NULL)-(double)(SUPER_TIME+1);
		key_direction = IDLE;

		while(on_level){

			// Lose check
			if(board.player.health<=0){
				// Exit game 
				on_level = false;
				close = true;
				continue;
			}

			// Check death
			int collidedGhost = ghostCollision(board.player.coords, &board);
			int super_time = (int)difftime(time(NULL), super_mode);
			if(collidedGhost!=-1){
				
				if(super_time<SUPER_TIME){
					// eat ghost
					(board.ghost_list)[collidedGhost].coords=initCoords(9*TILE_WIDTH, 9*TILE_HEIGHT+WIN_SCORE_HEIGHT); // TEMPORARY, need better init
					board.player.points+=GHOST_POINTS;
				}
				else{
					// death
					board.player.health--;
					on_level=false;
					printf("TODO : PACMAN DEATH ANIMATION\n");
					continue;
				}	
			}

			// Check win
			if(board.nbGum <= 0 && board.nbBigGum <= 0){
				// all gums eatten
				printf("WIN ! :)\n");
				printf("TODO : WIN SCREEN\n");
				on_level=false;
				load_type=CHANGE_LEVEL;
				continue;
			}

			// Get keys / direction
			processKeyboard(&close, &on_level, &key_direction);

			// Move
			movePlayer(&board, key_direction);
			moveGhosts(&board);

			// Actions
			eatGum(&board);
			eatBigGum(&board, &super_mode);

			printf("super mode:%d\n", (int)difftime(time(NULL), super_mode));


			//clear renderer
			clearRenderer(rend);

			//render objects
			renderWalls(&board, wall_tex, rend);
			renderGum(&board, gum_tex, rend);
			renderBigGum(&board, biggum_tex, rend);
			renderTexture(player_tex, rend, board.player.coords.x, board.player.coords.y, TILE_WIDTH, TILE_HEIGHT); // render the player
			if(super_time<SUPER_TIME){
				renderGhosts(&board, ghost_scared_tex, rend);
			}
			else{
				renderGhosts(&board, ghost_tex, rend);
			}
			
			renderPlayerHealth(&board, player_tex, rend);
			renderPoints(&board, points_font, White, rend);
			renderGate(&board, gate_tex, rend);
			
			// update display
			updateDisplay(rend);
			
			// SDL_Delay(500);
		}
	}
	SDL_Delay(500);
	printf("quit\n");
	QuitSDL(win, rend);
	return 0;
}