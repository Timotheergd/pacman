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
#include "src/gestionGraphique.h"
#include "src/wall.h"
#include "src/player.h"
#include "src/ghost.h"
#include "src/gate.h"
#include "src/gum.h"

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
	
	// TEST
	// printf("level %d:%s\n",level_number, level_content);
	// printBoardContent(&board);

	/// ********** SDL INIT **********
	initSDL();
	SDL_Window* win = createWindow("PACMAN", WIN_WIDTH, WIN_HEIGHT);
	SDL_Renderer* rend = createRenderer(win);

	// *** LOAD TEXTURES ***
	struct timeval stop, start;
	gettimeofday(&start, NULL);

	// Player Textures
	// player_tex_path[DIRECTION][PLAYER_TEXTURES_PER_DIRECTION_ANIMATION][]
	char player_tex_path[NB_DIRECTION][PLAYER_TEXTURES_PER_DIRECTION_ANIMATION][100] = {
		
		{	// right
			"assets/textures/pacman/pacman_right_close.png",
			"assets/textures/pacman/pacman_right_mid_open.png",
			"assets/textures/pacman/pacman_right_open.png",
			"assets/textures/pacman/pacman_right_open_big.png",
			"assets/textures/pacman/pacman_right_open.png",
			"assets/textures/pacman/pacman_right_mid_open.png"
		},
		{	// left
			"assets/textures/pacman/pacman_left_close.png",
			"assets/textures/pacman/pacman_left_mid_open.png",
			"assets/textures/pacman/pacman_left_open.png",
			"assets/textures/pacman/pacman_left_open_big.png",
			"assets/textures/pacman/pacman_left_open.png",
			"assets/textures/pacman/pacman_left_mid_open.png"
		},
		{	// up
			"assets/textures/pacman/pacman_up_close.png",
			"assets/textures/pacman/pacman_up_mid_open.png",
			"assets/textures/pacman/pacman_up_open.png",
			"assets/textures/pacman/pacman_up_open_big.png",
			"assets/textures/pacman/pacman_up_open.png",
			"assets/textures/pacman/pacman_up_mid_open.png"
		},
		{	// down
			"assets/textures/pacman/pacman_down_close.png",
			"assets/textures/pacman/pacman_down_mid_open.png",
			"assets/textures/pacman/pacman_down_open.png",
			"assets/textures/pacman/pacman_down_open_big.png",
			"assets/textures/pacman/pacman_down_open.png",
			"assets/textures/pacman/pacman_down_mid_open.png"
		},
		{	// idle
			"assets/textures/pacman/pacman_idle.png",
			"assets/textures/pacman/pacman_idle.png",
			"assets/textures/pacman/pacman_idle.png",
			"assets/textures/pacman/pacman_idle.png",
			"assets/textures/pacman/pacman_idle.png",
			"assets/textures/pacman/pacman_idle.png"
		}
	};
	SDL_Texture* player_tex[5][PLAYER_TEXTURES_PER_DIRECTION_ANIMATION];
	for(int i=0; i<5;i++){
		for(int j=0;j<PLAYER_TEXTURES_PER_DIRECTION_ANIMATION;j++){
			player_tex[i][j] = loadTexture(player_tex_path[i][j], rend);
		}
	}
	
	// Ghosts Textures
	// ghosts_tex_path[NUMBER_OF_GHOSTS(4+scared)][DIRECTION][]
	char ghosts_tex_path[4+2][NB_DIRECTION][100] = {
		{	// red
			"assets/textures/ghost/ghost_red_right.png",
			"assets/textures/ghost/ghost_red_left.png",
			"assets/textures/ghost/ghost_red_up.png",
			"assets/textures/ghost/ghost_red_down.png",
			"assets/textures/ghost/ghost_red_right.png"
		},
		{	// orange
			"assets/textures/ghost/ghost_orange_right.png",
			"assets/textures/ghost/ghost_orange_left.png",
			"assets/textures/ghost/ghost_orange_up.png",
			"assets/textures/ghost/ghost_orange_down.png",
			"assets/textures/ghost/ghost_orange_right.png"
		},
		{	// pink
			"assets/textures/ghost/ghost_pink_right.png",
			"assets/textures/ghost/ghost_pink_left.png",
			"assets/textures/ghost/ghost_pink_up.png",
			"assets/textures/ghost/ghost_pink_down.png",
			"assets/textures/ghost/ghost_pink_right.png"
		},
		{	// green
			"assets/textures/ghost/ghost_green_right.png",
			"assets/textures/ghost/ghost_green_left.png",
			"assets/textures/ghost/ghost_green_up.png",
			"assets/textures/ghost/ghost_green_down.png",
			"assets/textures/ghost/ghost_green_right.png"
		},
		// SCARED
		{	// blue
			"assets/textures/ghost/ghost_blue_scared_right.png",
			"assets/textures/ghost/ghost_blue_scared_left.png",
			"assets/textures/ghost/ghost_blue_scared_up.png",
			"assets/textures/ghost/ghost_blue_scared_down.png",
			"assets/textures/ghost/ghost_blue_scared_right.png"
		},
		{	// white
			"assets/textures/ghost/ghost_white_scared_right.png",
			"assets/textures/ghost/ghost_white_scared_left.png",
			"assets/textures/ghost/ghost_white_scared_up.png",
			"assets/textures/ghost/ghost_white_scared_down.png",
			"assets/textures/ghost/ghost_white_scared_right.png"
		}
	};
	SDL_Texture* ghosts_tex[6][NB_DIRECTION];
	for(int i=0; i<6;i++){
		for(int j=0;j<NB_DIRECTION;j++){
			ghosts_tex[i][j] = loadTexture(ghosts_tex_path[i][j], rend);
		}
	}
	
	// Player death animation textures
	char player_death_tex_path[PLAYER_NB_DEATH_TEXTURE_ANIMATION][100] = {
		"assets/textures/pacman/death/pacman_death01.png",
		"assets/textures/pacman/death/pacman_death02.png",
		"assets/textures/pacman/death/pacman_death03.png",
		"assets/textures/pacman/death/pacman_death04.png",
		"assets/textures/pacman/death/pacman_death05.png",
		"assets/textures/pacman/death/pacman_death06.png",
		"assets/textures/pacman/death/pacman_death07.png",
		"assets/textures/pacman/death/pacman_death08.png",
		"assets/textures/pacman/death/pacman_death09.png",
		"assets/textures/pacman/death/pacman_death10.png",
	};
	SDL_Texture* player_death_tex[PLAYER_NB_DEATH_TEXTURE_ANIMATION];
	for(int i=0;i<PLAYER_NB_DEATH_TEXTURE_ANIMATION;i++){
		player_death_tex[i] = loadTexture(player_death_tex_path[i], rend);
	}
	

	SDL_Texture* wall_tex = loadTexture("assets/textures/wall.png", rend);
	SDL_Texture* gum_tex = loadTexture("assets/textures/gum/gum.png", rend);
	SDL_Texture* biggum_tex = loadTexture("assets/textures/gum/biggum.png", rend);
	SDL_Texture* gate_tex = loadTexture("assets/textures/red_gate.png", rend);

	SDL_Texture* blank_tex = loadTexture("assets/textures/blank.png", rend);

	// *********** FONTS **********
	TTF_Init();
	SDL_Color White = {255, 255, 255};
	TTF_Font* points_font = loadFont("assets/Fonts/emulogic.ttf", 10);
	
	// ********** GAME VARIABLES **********
	Direction key_direction = IDLE;
	bool close = false;
	bool on_level = true;

	while(!close){
		SDL_Event event;

		// printf("HERE WE GO AGAIN !\n");
	
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
					// eat ghost
					(board.ghost_list)[collidedGhost].coords=((board.ghost_list)[collidedGhost]).respawnPoint;
					((board.ghost_list)[collidedGhost]).death_time=time(NULL);
					((board.ghost_list)[collidedGhost]).vulnerable_time=0;
					board.player.streak+=1;
					board.player.points+=GHOST_POINTS*(int)pow(2,board.player.streak-1);
				}
				else{
					// death
					board.player.health--;
					on_level=false;
					updateDisplay(rend);
					// renser death animation
					for(int i=0;i<PLAYER_NB_DEATH_TEXTURE_ANIMATION;i++){
						renderTexture(blank_tex, rend, board.player.coords.x, board.player.coords.y, TILE_WIDTH, TILE_HEIGHT);
						renderTexture(player_death_tex[i], rend, board.player.coords.x, board.player.coords.y, TILE_WIDTH, TILE_HEIGHT);
						updateDisplay(rend);
						SDL_Delay(100);
					}
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
			// Reset Player streak
			int nb_ghost_eatable=0;
			for(int i=0;i<4;i++){// TODO : MAKE A FUNCTION
				if((int)difftime(time(NULL), ((board.ghost_list)[i]).vulnerable_time)<SUPER_TIME){
					nb_ghost_eatable++;
				}
			}
			if(nb_ghost_eatable==0){
				board.player.streak=0;
			}
			
			eatGum(&board);
			eatBigGum(&board);
			// printf("super mode:%d\n", super_time);

			//clear renderer
			clearRenderer(rend);

			//render objects
			renderWalls(&board, wall_tex, rend);
			renderGum(&board, gum_tex, rend);
			renderBigGum(&board, biggum_tex, rend);
			
			// Player
			gettimeofday(&stop, NULL);
			int nb_usec_since_launch = abs(stop.tv_usec - start.tv_usec);
			renderTexture(player_tex[board.player.direction][(nb_usec_since_launch/(1000000/PLAYER_MOVE_NB_FRAME_PER_SEC))%PLAYER_TEXTURES_PER_DIRECTION_ANIMATION], rend, board.player.coords.x, board.player.coords.y, TILE_WIDTH, TILE_HEIGHT); // render the player
			
			// Ghost
			renderGhosts(&board, &ghosts_tex, rend, nb_usec_since_launch);
			
			renderPlayerHealth(&board, player_tex[0][1], rend);
			renderPoints(&board, points_font, White, rend);
			renderGate(&board, gate_tex, rend);
			
			// update display
			updateDisplay(rend);
			
			// SDL_Delay(500);
		}
	}
	printf("score:%d\nquit\n", board.player.points);
	return 0;
}