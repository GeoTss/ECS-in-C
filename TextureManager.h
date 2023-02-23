#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"

static inline SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* filename){
	SDL_Surface* surf = IMG_Load(filename);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf);
//	SDL_Texture* tex = IMG_LoadTexture(renderer, filename);
	printf("Texture: %p\n", tex);
	if(tex == NULL){
		printf("FAILED TO LOAD TEXTURE!\n");
		exit(1);
	}
	return tex;
} 

static inline void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect){
	SDL_RenderCopy(renderer, texture, srcRect, destRect);
}

#endif
