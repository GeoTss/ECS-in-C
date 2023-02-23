#ifndef KEYBOARD_COMPONENT_H
#define KEYBOARD_COMPONENT_H

#include "ECS.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "TransformComponent.h"
#include "Vector2f.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

typedef struct{
	Component component;
	SDL_Event* KeyboardEvent;
	TransformComponent* transformComponent;
} KeyboardComponent;

static inline void updateKeyboardComponent(void* c){
	KeyboardComponent* k = (KeyboardComponent*)c;
	
	if(k->KeyboardEvent->type == SDL_KEYDOWN){
		switch(k->KeyboardEvent->key.keysym.sym){
			case SDLK_w:
				k->transformComponent->velocity.y = -1;
				break;
			case SDLK_s:
				k->transformComponent->velocity.y = 1;
				break;
			case SDLK_a:
				k->transformComponent->velocity.x = -1;
				break;
			case SDLK_d:
				k->transformComponent->velocity.x = 1;
				break;
			case SDLK_LSHIFT:
				k->transformComponent->velocity = multiplyVector2fNum(&k->transformComponent->velocity, 2);
				break;
		}
	}

	if(k->KeyboardEvent->type == SDL_KEYUP){
		switch(k->KeyboardEvent->key.keysym.sym){
			case SDLK_w:
				k->transformComponent->velocity.y = 0;
				break;
			case SDLK_s:
				k->transformComponent->velocity.y = 0;
				break;
			case SDLK_a:
				k->transformComponent->velocity.x = 0;
				break;
			case SDLK_d:
				k->transformComponent->velocity.x = 0;
				break;
			case SDLK_LSHIFT:
				k->transformComponent->velocity = divideVector2fNum(&k->transformComponent->velocity, 2);
		}
	}
}

static inline KeyboardComponent* KeyboardComponentConstructor(Entity* owner, SDL_Event* e){
	
	KeyboardComponent* new_comp = (KeyboardComponent*)malloc(sizeof(KeyboardComponent));
		
	new_comp->component.owner = owner;

	new_comp->KeyboardEvent = e;
	if(!ECShasComponent(TransformComponent, owner)){
		addComponent(TransformComponent, owner, Vector2fConstructor(0, 0), Vector2fConstructor(1, 1));
		printf("Keyboard: owner didn't have TransformComponent\n");
	}
	new_comp->transformComponent = ECSgetComponent(TransformComponent, owner);

	new_comp->component.updateComponent = &updateKeyboardComponent;
	new_comp->component.initComponent = &defaultComponentFunc;
	new_comp->component.drawComponent = &defaultComponentFunc;

	return new_comp;
}

#endif
