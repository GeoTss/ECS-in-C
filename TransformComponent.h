#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "ECS.h"
#include "I_Printable.h"
#include "Vector2f.h"
#include <stdlib.h>

struct TransformComponent{
	Component component;
	I_Printable printInterface;
	Vector2f position, velocity, speed;
};
typedef struct TransformComponent TransformComponent;
 
static inline void updateTransformComponent(void* c){
	//((TransformComponent*)c)->position = addVector2f(&((TransformComponent*)c)->position, &((TransformComponent*)c)->velocity);
	TransformComponent* t = (TransformComponent*)c;
	t->position.x += t->velocity.x * (t->speed.x);
	t->position.y += t->velocity.y * (t->speed.y);
}

static inline char* printTransformComponent(void* c){
	char* msg;
	asprintf(&msg, "Name: Transform Component\nCoordinates: (x:%2f, y:%2f)\nVelocity: (x:%2f, y:%2f)", ((TransformComponent*)c)->position.x, \
	((TransformComponent*)c)->position.y, ((TransformComponent*)c)->velocity.x, ((TransformComponent*)c)->velocity.y);
	return msg;
}

static inline TransformComponent* TransformComponentConstructor(Entity* owner, Vector2f positionVector, Vector2f speedVector){
	TransformComponent* new_comp = (TransformComponent*)malloc(sizeof(TransformComponent));
	
	new_comp->position = positionVector;
	new_comp->speed = speedVector;
	new_comp->velocity = Vector2fConstructor(0, 0);

	new_comp->component.updateComponent = &updateTransformComponent;
	new_comp->component.drawComponent = &defaultComponentFunc;
	new_comp->component.initComponent = &defaultComponentFunc;

	new_comp->printInterface.getPrintable = &printTransformComponent;
	new_comp->printInterface.owner = new_comp;

	new_comp->component.owner = owner;

	return new_comp;
};
#endif
