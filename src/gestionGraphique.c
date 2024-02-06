#include "gestionGraphique.h"


void initSDL(){
if(SDL_Init(SDL_INIT_VIDEO) < 0)  // initialisation de la SDL
    {
       printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
       SDL_Quit();
    }
}


SDL_Window * createWindow(char winName[], int winWidth, int winHeigth){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
			printf("SDL_Init Error\n");
    }
    SDL_Window *win = SDL_CreateWindow(winName, SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, winWidth, winHeigth, SDL_WINDOW_SHOWN);
    if (win == NULL){
		printf("SDL_CreateWindow Error\n");
		SDL_Quit();
    }
    return win;
}

SDL_Renderer * createRenderer(SDL_Window *win){
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL){
		SDL_DestroyWindow(win);
		printf("SDL_CreateRenderer Error");
		SDL_Quit();
	}
	return ren;
}

SDL_Texture* loadTexture(const char* file, SDL_Renderer *ren){
	SDL_Texture *texture = NULL;
	SDL_Surface *loadedImage = IMG_Load(file);
	if (loadedImage != NULL){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == NULL){
			printf("Error : CreateTextureFromSurface\n");
		}
	}
	else {
		printf("Error : LoadBMP\n");
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int width, int height){
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void updateDisplay(SDL_Renderer *ren){
	SDL_RenderPresent(ren);
}

void clearRenderer(SDL_Renderer *ren){
	SDL_RenderClear(ren);
}

void processKeyboard(bool *close, bool *on_level, Direction *direction){
	SDL_Event event;
	int key,button;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				// handling of close button
				*close = true;
				*on_level = false;
				break;
			// Get direction
			case SDL_KEYDOWN:
				// keyboard API for key pressed
				switch (event.key.keysym.scancode) {
					case SDL_SCANCODE_W:
					case SDL_SCANCODE_UP:
						*direction=UP;
						break;
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_LEFT:
						*direction=LEFT;
						break;
					case SDL_SCANCODE_S:
					case SDL_SCANCODE_DOWN:
						*direction=DOWN;
						break;
					case SDL_SCANCODE_D:
					case SDL_SCANCODE_RIGHT:
						*direction=RIGHT;
						break;
					default:
						// direction=IDLE;
						break;
				}
		}
	}
}

void QuitSDL(SDL_Window *win, SDL_Renderer *ren){
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit(); 
}

