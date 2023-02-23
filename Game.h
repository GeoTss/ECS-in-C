#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_video.h"
#include <SDL2/SDL.h>
#include "ECS.h"

typedef struct{
	Manager* manager;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event event;
} Game;

 void draw(Game*);
 void update(Game*);
 void initGame(Game*, const char*, int, int, short);

#endif
