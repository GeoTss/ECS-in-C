#include "Game.h"
#include "ECS.h"
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"

 void initGame(Game* g, const char* title, int width, int height, short fullscreen){
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	g->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen);
	g->renderer = SDL_CreateRenderer(g->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

 void update(Game* g){
	updateManagerEntities(g->manager);	
}

 void draw(Game* g){
	SDL_RenderClear(g->renderer);
	drawManagerEntities(g->manager);
	SDL_RenderPresent(g->renderer);
}
