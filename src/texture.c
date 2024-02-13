#include "textures.h"


void load_PlayerTextures(SDL_Texture* player_tex[NB_DIRECTION][PLAYER_NB_TEXTURES_PER_DIRECTION_ANIMATION], SDL_Renderer *rend){
	// Player Textures
	char player_tex_path[NB_DIRECTION][PLAYER_NB_TEXTURES_PER_DIRECTION_ANIMATION][100] = {
		
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
	for(int i=0; i<NB_DIRECTION;i++){
		for(int j=0;j<PLAYER_NB_TEXTURES_PER_DIRECTION_ANIMATION;j++){
			player_tex[i][j] = loadTexture(player_tex_path[i][j], rend);
		}
	}
}

void load_GhostsTextures(SDL_Texture* ghosts_tex[6][NB_DIRECTION], SDL_Renderer *rend){
    // Ghosts Textures
    // 4 ghosts colors + 2 colors if scared
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
	for(int i=0; i<6;i++){
		for(int j=0;j<NB_DIRECTION;j++){
			ghosts_tex[i][j] = loadTexture(ghosts_tex_path[i][j], rend);
		}
	}
}

void load_PlayerDeathTextures(SDL_Texture* player_death_tex[PLAYER_NB_DEATH_TEXTURE_ANIMATION], SDL_Renderer *rend){
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
	for(int i=0;i<PLAYER_NB_DEATH_TEXTURE_ANIMATION;i++){
		player_death_tex[i] = loadTexture(player_death_tex_path[i], rend);
	}
}