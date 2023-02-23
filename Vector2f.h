#ifndef VECTOR2F_H
#define VECTOR2F_H

#include "I_Printable.h"
#include <stdlib.h>

typedef struct{
	float x, y;
	I_Printable printInterface;
} Vector2f;

static inline char* printVector2f(void* c){
	char* buf;
	asprintf(&buf, "Name: Vector2f\nCoordinates: (x:%2f, y:%2f)", ((Vector2f*)c)->x, ((Vector2f*)c)->y);
	return buf;
}

static inline Vector2f Vector2fConstructor(float x, float y){
	Vector2f new_v;
	new_v.x = x;
	new_v.y = y;

	new_v.printInterface.getPrintable = &printVector2f;
	new_v.printInterface.owner = &new_v;

	return new_v;
}

static inline Vector2f addVector2f(Vector2f* v1, Vector2f* v2){
	return Vector2fConstructor(v1->x + v2->x, v1->y + v2->y);
}

static inline Vector2f substractVector2f(Vector2f* v1, Vector2f* v2){
	return Vector2fConstructor(v1->x - v2->x, v1->y - v2->y);	
}

static inline Vector2f multiplyVector2f(Vector2f* v1, Vector2f* v2){
	return Vector2fConstructor(v1->x * v2->x, v1->y * v2->y);	
}


static inline Vector2f divideVector2f(Vector2f* v1, Vector2f* v2){
	if(v2->x == 0 || v2->y == 0)
		return Vector2fConstructor(0, 0);
	return Vector2fConstructor(v1->x / v2->x, v1->y / v2->y);
}

static inline Vector2f multiplyVector2fNum(Vector2f* v, int n){
	return Vector2fConstructor(v->x * n, v->y * n);
}

static inline Vector2f divideVector2fNum(Vector2f* v, int n){
	if(n == 0)
		return Vector2fConstructor(0, 0);
	return Vector2fConstructor(v->x * n, v->y * n);
}

#endif
