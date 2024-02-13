#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "src/ressources.h"
#include "src/board.h"
#include "src/graphics.h"
#include "src/wall.h"
#include "src/player.h"
#include "src/ghost.h"
#include "src/gate.h"
#include "src/gum.h"
#include "src/textures.h"

int main(int argc, char *argv[]){

	/// ********** BOARD INIT **********
	// read file
	char level_file[50]="levels.txt";
	char level_content[LEVEL_SIZE]="";
	int level_number=8;
	read_level(level_file, level_number, &level_content);
	
	// init board
	Board board=initBoard();
	LoadType load_type=NEW;
	loadBoard(&level_content, &board, load_type);
	load_type=RELOAD;

	/// ********** SDL INIT **********
	initSDL();
	SDL_Window* win = createWindow("PACMAN", WIN_WIDTH, WIN_HEIGHT);
	SDL_Renderer* rend = createRenderer(win);

	// *** LOAD TEXTURES ***
	struct timeval stop, start;
	gettimeofday(&start, NULL);

	SDL_Texture* player_tex[NB_DIRECTION][PLAYER_NB_TEXTURES_PER_DIRECTION_ANIMATION];
	SDL_Texture* ghosts_tex[6][NB_DIRECTION];
	SDL_Texture* player_death_tex[PLAYER_NB_DEATH_TEXTURE_ANIMATION];
	load_PlayerTextures(player_tex, rend);
	load_GhostsTextures(ghosts_tex, rend);
	load_PlayerDeathTextures(player_death_tex, rend);
	SDL_Texture* blank_tex = loadTexture("assets/textures/blank.png", rend);
	SDL_Texture* wall_tex = loadTexture("assets/textures/wall.png", rend);
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
	int level = 1;

	while(!close){
		SDL_Event event;
	
		// Reset values
		on_level=true;
		loadBoard(&level_content, &board, load_type);
		load_type=RELOAD;
		key_direction = IDLE;

		while(on_level){
			// Check lose
			if(board.player.health<=0){
				// Exit game 
				on_level = false;
				close = true;
				continue;
			}

			// Check death
			int collidedGhost = ghostCollision(board.player.coords, &board);
			if(collidedGhost!=-1){
				
				if((int)difftime(time(NULL), ((board.ghost_list)[collidedGhost]).vulnerable_time)<SUPER_TIME){
					eatGhost(&board, collidedGhost);
				}
				else{
					// death
					board.player.health--;
					on_level=false;
					updateDisplay(rend);
					renderPlayerDeath(&board, &player_death_tex, blank_tex, rend);
					continue;
				}	
			}

			// Check win
			if(board.nbGum <= 0 && board.nbBigGum <= 0){ // if all gums and bigGums eatten
				on_level=false;
				load_type=CHANGE_LEVEL;
				level++;
				if(level%5==0) allGhostIncrSpeed(&board, 1); // increase speed every 5 level
				continue;
			}

			// *** Get keys / direction ***
			processKeyboard(&close, &on_level, &key_direction);

			// *** Move ***
			movePlayer(&board, key_direction);
			moveGhosts(&board);

			// *** Actions ***
			updatePlayerStreak(&board);
			eatGum(&board);
			eatBigGum(&board);

			// Time in millisec since to change the texture depending on time
			gettimeofday(&stop, NULL);
			int nb_usec_since_launch = abs(stop.tv_usec - start.tv_usec);

			// *** Render objects ***
			//clear renderer
			clearRenderer(rend);
			
			renderWalls(&board, wall_tex, rend);
			renderGum(&board, gum_tex, rend);
			renderBigGum(&board, biggum_tex, rend);
			renderPlayer(&board, &player_tex, rend, nb_usec_since_launch);
			renderGhosts(&board, &ghosts_tex, rend, nb_usec_since_launch);
			renderPlayerHealth(&board, player_tex[0][1], rend);
			renderPoints(&board, points_font, White, rend);
			renderLevel(&board, points_font, White, rend, level);
			renderGate(&board, gate_tex, rend);
			
			// update display
			updateDisplay(rend);
		}
	}
	printf("score:%d\nquit\n", board.player.points);
	return 0;
}