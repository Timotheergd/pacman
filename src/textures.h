#ifndef TEXTURES_H
#define TEXTURES_H

#include "ressources.h"
#include "graphics.h"

void load_PlayerTextures(SDL_Texture* player_tex[NB_DIRECTION][PLAYER_NB_TEXTURES_PER_DIRECTION_ANIMATION], SDL_Renderer *rend);
void load_GhostsTextures(SDL_Texture* ghosts_tex[6][NB_DIRECTION], SDL_Renderer *rend);
void load_PlayerDeathTextures(SDL_Texture* player_death_tex[PLAYER_NB_DEATH_TEXTURE_ANIMATION], SDL_Renderer *rend);

#endif