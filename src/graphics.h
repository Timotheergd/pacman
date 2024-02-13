#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ressources.h"

void initSDL();
SDL_Window * createWindow(char winName[], int winWidth, int winHeigth);
SDL_Renderer * createRenderer(SDL_Window *win);
SDL_Texture* loadTexture(const char* file, SDL_Renderer *ren);
TTF_Font* loadFont(const char* file, int size);
SDL_Texture* loadText(const char* text,TTF_Font* font, SDL_Color color,  SDL_Renderer *rend);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int width, int height);
void updateDisplay(SDL_Renderer *ren);
void clearRenderer(SDL_Renderer *ren);
void processKeyboard(bool *close, bool *on_level, Direction *direction);
void QuitSDL(SDL_Window *win, SDL_Renderer *ren);

#endif