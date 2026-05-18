
#ifndef _DEVICE_H_
#define _DEVICE_H_ 1


#include "symbols.h"
#include "vector.h"

typedef struct{
    char *name;
    int pos;
}FBVAR;

typedef struct{
    char *name;
    VECTOR *vars;
}FUNC_BLOCK;


void dev_init();
void dev_addfb(char *name);
void dev_addVar(char *name, char *var, int pos);
int dev_getVarPos(char *var, char *fb);


#endif // _DEVICE_H_

