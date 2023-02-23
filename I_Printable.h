#ifndef PRINTABLE_H
#define PRINTABLE_H

#include "ECS.h"
#include <stdlib.h>

typedef struct{
    char* (*getPrintable)(void*);
	void* owner;
} I_Printable;

char* defaultGetPrintable(){ return ""; }

static inline char* printComponentElems(I_Printable* c){
	return c->getPrintable(c->owner);
}

#define getPrintableCut(TYPE, elem)\
	print##TYPE(elem)
    //(ECShasComponent(TYPE, e)) ? ECSgetComponent(TYPE, e)->printInterface.getPrintable(ECSgetComponent(TYPE, e)): ""

#endif
