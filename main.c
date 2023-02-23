#include <stdio.h>
#include <stdlib.h>
#include "ECS.h"
#include "I_Printable.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_video.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "KeyboardComponent.h"
#include "Vector2f.h"
#include "Game.h"

int main(int argc, char* argv[]){

	Manager* manager = managerInit();
	Entity* entity1 = makeEntity(manager);

	Game* g = (Game*)malloc(sizeof(Game));
	g->manager = manager;
	initGame(g, "Test", 500, 500, 0);

	printf("Manager count: %d\n", manager->count);

	addComponent(TransformComponent, entity1, Vector2fConstructor(30, 40), Vector2fConstructor(7, 6));

	printf("TransformComponentID: %d\n", ComponentID(TransformComponent));
	printf("SpriteComponentID:%2d\n", ComponentID(SpriteComponent));
	printf("KeyboardComponentID:%2d\n", ComponentID(KeyboardComponent));
	printf("How many components are there:%2d\n" , COMP_IDS_COUNT);

	updateManagerEntities(manager);
	// printf("TransformComponent: (%d, %d)\n", getComponent(TransformComponent, e)->x, getComponent(TransformComponent, e)->y);
	//printf(getPrintableCut(TransformComponent, e));
	//addComponent(RandomComponent, e, 3.f, 10.2f, "Hello world");
	updateManagerEntities(manager);
	if(ECShasComponent(TransformComponent, entity1)){
		printf("%s\n", printComponentElems(&ECSgetComponent(TransformComponent, entity1)->printInterface));
		printf("%s\n", printComponentElems(&ECSgetComponent(TransformComponent, entity1)->position.printInterface));
		//printf("%s\n", getPrintableCut(TransformComponent, entity1));
		//printf("%s\n", printVector2f(&ECSgetComponent(TransformComponent, entity1)->position));
	}
	printf("\n");

	SDL_Rect src, dest;
	src.x = src.y = 0;
	src.w = src.h = 32;

	dest.x = dest.y = 50;
	dest.w = dest.h = 64;
	//const char* grass = "./circle.png";
	addComponent(SpriteComponent, entity1, &g->renderer, &src, &dest, "./circle.png");
	//printf("%s", printSpriteComponent(ECSgetComponent(SpriteComponent, entity1)));
	printf("%s", printComponentElems(&ECSgetComponent(SpriteComponent, entity1)->printInterface));
	
	printf("entity1: %p", entity1);
	deleteComponent(TransformComponent, entity1);
	
	addComponent(KeyboardComponent, entity1, &g->event);
	//addComponent(SpriteComponent, entity2, 4, 6);

	int running = 1;
	while(running){
		SDL_PollEvent(&g->event);
		switch(g->event.type){
			case SDL_QUIT:
				running = 0;		
			break;
		}
		draw(g);
		update(g);
		//printf("%s\n", printComponentElems(&ECSgetComponent(TransformComponent, entity1)->printInterface));
	}

	destroyManager(manager);
	SDL_DestroyRenderer(g->renderer);
	SDL_DestroyWindow(g->window);
	SDL_Quit();

	return 0;
}

