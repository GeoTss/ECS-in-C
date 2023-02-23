#ifndef ECS_H
#define ECS_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
struct Entity;
struct Component;
struct Manager;

#define MAX_COMPONENTS 12
#define MAX_ENTITIES 8

typedef enum{TransformComponent_ID, SpriteComponent_ID, KeyboardComponent_ID, COMP_IDS_COUNT} COMP_IDS;

struct Component{
	struct Entity* owner;
	void (*updateComponent)(void*);
	void (*drawComponent)(void*);
	void (*initComponent)(void*);
};
typedef struct Component Component;

static void defaultComponentFunc(void* c) {}

static inline void ECScomponentInit(Component* c, struct Entity* _owner){
	c->owner = _owner;
	c->drawComponent = &defaultComponentFunc;
	c->initComponent = &defaultComponentFunc;
	c->updateComponent = &defaultComponentFunc;
}

#define ComponentConstructor(TYPE, ...)\
	TYPE##Constructor(__VA_ARGS__);

#define ComponentID(TYPE) TYPE##_ID

#define ComponentConstructor(TYPE, ...)\
	TYPE##Constructor(__VA_ARGS__);

#define ECSaddComponent(TYPE, e, ...)\
	e->componentArray[ComponentID(TYPE)] = (TYPE*)ComponentConstructor(TYPE, e, __VA_ARGS__);\
	e->componentBitset[ComponentID(TYPE)] = 1;\
	e->active = 1;\

#define ECSdeleteComponent(TYPE, e)\
	if(ECShasComponent(TYPE, e)){\
		free(e->componentArray[ComponentID(TYPE)]);\
		e->componentArray[ComponentID(TYPE)] = (Component*)malloc(sizeof(Component));\
		ECScomponentInit(e->componentArray[ComponentID(TYPE)], e);\
		e->componentBitset[ComponentID(TYPE)] = 0;\
	}

#define ECSgetComponent(TYPE, e) ((TYPE*)e->componentArray[ComponentID(TYPE)])
#define ECShasComponent(TYPE, e) e->componentBitset[ComponentID(TYPE)]

struct Entity{
	void* componentArray[MAX_COMPONENTS];
	short componentBitset[MAX_COMPONENTS];
	short active;
};
typedef struct Entity Entity;

static inline void initEntity(Entity* e){
	for(int i=0; i < MAX_COMPONENTS; ++i){
		e->componentArray[i] = malloc(sizeof(Component));
		ECScomponentInit((Component*)e->componentArray[i], e);
	}
}

static inline void updateEntityComponents(Entity* e){
	for(int i=0; i < MAX_COMPONENTS; ++i)
		((Component*)(e->componentArray[i]))->updateComponent((void*)e->componentArray[i]);
}

static inline void drawEntityComponents(Entity* e){
	for(int i=0; i < MAX_COMPONENTS; ++i)
		((Component*)(e->componentArray[i]))->drawComponent((void*)e->componentArray[i]);
}

struct Manager{
	Entity* enitities[MAX_ENTITIES];
	int count;
};
typedef struct Manager Manager;

static Entity* makeEntity(Manager* m){
	Entity* new_entity = (Entity*)malloc(sizeof(Entity));
	m->enitities[m->count++] = new_entity;
	initEntity(new_entity);
	return new_entity;
}

static inline Manager* managerInit(){
	Manager* m = (Manager*)malloc(sizeof(Manager));
	m->count = 0;
	for(int i = 0; i < MAX_ENTITIES; ++i)
		m->enitities[i] = NULL;
	return m;
}

static inline void updateManagerEntities(Manager* m){
	for(int i=0; i < m->count; ++i)
		updateEntityComponents(m->enitities[i]);
}

static inline void drawManagerEntities(Manager* m){
	for(int i=0; i < m->count; ++i)
		drawEntityComponents(m->enitities[i]);
}

static inline void destroyManager(Manager* manager){
	for(int i = 0; i < manager->count; ++i){
		for(int j=0; j < MAX_COMPONENTS; ++j)
			if(manager->enitities[i]->componentBitset[j]){
				// printf("Deleting %p",manager->enitities[i]->componentArray[j]);
				free(manager->enitities[i]->componentArray[j]);
				manager->enitities[i]->componentBitset[j] = 0;
			}
		free(manager->enitities[i]);
	}
	free(manager);
}

#ifdef DEBUG
	#define addComponent(TYPE, e, ...)\
		printf("\nAdding " #TYPE " to " #e " in file %s, in line %d\n", __FILE__, __LINE__);\
		ECSaddComponent(TYPE, e, __VA_ARGS__);\
		printf(#TYPE " added\n");
	
	#define deleteComponent(TYPE, e)\
		printf("\nDeleting " #TYPE " from " #e " in file %s, in line %d\n", __FILE__, __LINE__);\
		ECSdeleteComponent(TYPE, e);\
		printf(#TYPE " deleted\n");
#else
	#define addComponent(TYPE, e, ...) ECSaddComponent(TYPE, e, __VA_ARGS__)
	#define deleteComponent(TYPE, e) ECSdeleteComponent(TYPE, e)
#endif

#endif
