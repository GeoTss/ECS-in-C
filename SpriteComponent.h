#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "ECS.h"
#include "Game.h"
#include "I_Printable.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_render.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include "Vector2f.h"

typedef struct{
    Component component;
    I_Printable printInterface;
    SDL_Renderer** renderer_ptr;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    TransformComponent* transformComponent;
} SpriteComponent;

void updateSpriteComponent(void* c){
    ((SpriteComponent*)c)->destRect.x = ((SpriteComponent*)c)->transformComponent->position.x;
    ((SpriteComponent*)c)->destRect.y = ((SpriteComponent*)c)->transformComponent->position.y;
}

void drawSpriteComponent(void* c){
    SDL_RenderCopy(*((SpriteComponent*)c)->renderer_ptr, ((SpriteComponent*)c)->texture, &((SpriteComponent*)c)->srcRect, &((SpriteComponent*)c)->destRect);
    //Draw(((SpriteComponent*)c)->texture, &((SpriteComponent*)c)->srcRect, &((SpriteComponent*)c)->destRect);
}

static inline char* printSpriteComponent(void* c){
    char* msg;
    asprintf(&msg, \
"Name: SpriteComponent\n\
Source Rectangle Info:\n\
X:%2d\n\
Y:%2d\n\
Width:%2d\n\
Height:%2d\n\
Destination Rectangle:\n\
X:%2d\n\
Y:%2d\n\
Width:%2d\n\
Height:%2d\n",\
((SpriteComponent*)c)->srcRect.x, ((SpriteComponent*)c)->srcRect.y, ((SpriteComponent*)c)->srcRect.w, ((SpriteComponent*)c)->srcRect.h,\
((SpriteComponent*)c)->destRect.x, ((SpriteComponent*)c)->destRect.y, ((SpriteComponent*)c)->destRect.w, ((SpriteComponent*)c)->destRect.h);
    
    return msg;
}

static inline SpriteComponent* SpriteComponentConstructor(Entity* owner, SDL_Renderer** renderer_ptr, SDL_Rect* srcRect, SDL_Rect* destRect, const char* filename){
    SpriteComponent* new_comp = (SpriteComponent*)malloc(sizeof(SpriteComponent));
    
    new_comp->component.owner = owner;

    new_comp->srcRect = *srcRect;
    new_comp->destRect = *destRect;
    new_comp->renderer_ptr = renderer_ptr;
    new_comp->texture = LoadTexture(*renderer_ptr, filename);

    new_comp->component.drawComponent = &drawSpriteComponent;
    new_comp->component.initComponent = &defaultComponentFunc;
    new_comp->component.updateComponent = &updateSpriteComponent;

    new_comp->printInterface.getPrintable = &printSpriteComponent;
    new_comp->printInterface.owner = new_comp;
    
    if(!ECShasComponent(TransformComponent, owner)){
        addComponent(TransformComponent, owner, Vector2fConstructor(0, 0), Vector2fConstructor(1, 1));
        printf("Sprite: owner didn't have TransformComponent");
    }

    new_comp->transformComponent = ECSgetComponent(TransformComponent, owner);
    return new_comp;
}

#endif
