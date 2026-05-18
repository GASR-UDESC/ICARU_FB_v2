
#include "errors.h"
#include "symbols.h"
#include "algcode.h"
#include "atributos.h"
#include "ecc.h"
#include <string.h>
#include <stdio.h>
#include "device.h"
#include "ospath.h"


SYMBOL symbols[100];
ALGINST *alginit;
int asize;

char sy_output[10000];

void sy_setOutput(char *output){
    strcpy(sy_output, output);
}

int sy_calcNextPos()
{
    int j, pos;
    j = 0;
    pos = 0;
    while(symbols[j].i == 1)
    {
        if(symbols[j].isFunction == 0)
        {
            pos = pos + symbols[j].size;
        }
        j++;
    }
    return pos;
}

void sy_getEvtVars(int *start, int *count){
    int i,a,b;
    a = -1;
    b = 0;
    i=0;
    while(symbols[i].i == 1)
    {

        if(a == -1 && symbols[i].isEvt){
            a = i;
        }
        if(symbols[i].isEvt){
            b++;
        }
        i++;
    }
    *start = a;
    *count = b;
}

/* */
void sy_init()
{
    int i;
    for(i = 0; i < 100; i++)
    {
        symbols[i].i = 0;
    }
}
int sy_add(char *name, int type, int isFunction, int isEvt)
{
    int j;
    j = 0;
    while(symbols[j].i == 1)
    {
        j++;
    }
    symbols[j].name = strdup(name);
    symbols[j].type = type;
    symbols[j].isFunction = isFunction;
    symbols[j].isEvt = isEvt;
    symbols[j].init = 0;
    switch(type)
    {
    case TY_INT:
        symbols[j].size = 2;
        break;
    case TY_REAL:
        symbols[j].size = 4;
        break;
    case TY_BYTE:
        symbols[j].size = 1;
        break;
    }

    if(isFunction)
    {
        symbols[j].pos = alg_getNextPos();
        //printf("%s at %d\n",name, symbols[j].pos);
    }
    else
    {
        if(j == 0)
        {
            symbols[j].pos = 0;
        }
        else
        {
            symbols[j].pos = sy_calcNextPos();
        }


    }
    symbols[j].i = 1 ;
    return j;
}

/**
Adicionar com inicialzação.
*/
void sy_addi(char *name, int type, int isFunction, int isEvt, int init, int v_init, char *sv_init)
{
    int p;
    p = sy_add(name, type, isFunction, isEvt);
   // printf("%s %d\n", name, p);
    if(type==TY_INT)
    {
        symbols[p].init = 1;
        symbols[p].v_init = v_init;
    }
}
int sy_getPos(char *name)
{
    int j;
    j = 0;
    if(symbols[j].i == 0)
    {
        printf("var '%s' undeclared\n", name);
        err_printFatalError("");
    }
    while(strcmp(symbols[j].name,name) != 0)
    {
        j++;
        if(symbols[j].i == 0)
        {
            printf("var '%s' undeclared\n", name);
            err_printFatalError("");
        }
    }
    //printf("RET: %s at %d\n", name, symbols[j].pos);
    return symbols[j].pos;
}

int sy_getType(char *name){
    int j;
    j = 0;
    if(symbols[j].i == 0)
    {
        printf("var '%s' undeclared\n", name);
        err_printFatalError("");
    }
    while(strcmp(symbols[j].name,name) != 0)
    {
        j++;
        if(symbols[j].i == 0)
        {
            printf("var '%s' undeclared\n", name);
            err_printFatalError("");
        }
    }
    return symbols[j].type;
}

int sy_getTotalSize()
{
    return sy_calcNextPos();
}

int sy_generateInit()
{
    int j, l;
    j = 0;
    l = alg_newLabel();
    //alg_reset();

    alg_gen(I_ALLOC, sy_getTotalSize());
    while(symbols[j].i == 1)
    {
        if(symbols[j].init)
        {
            alg_gen(I_CONST, symbols[j].v_init);
            alg_gen(I_STORE, symbols[j].pos);
        }
        j++;
    }


    alg_gen(I_CONST, ecc_getInitialState());
    alg_gen(I_STORE, sy_getPos("__est"));
    alg_gen(I_CONST, 1);
    alg_gen(I_STORE, sy_getPos("__alg"));
    alg_gen(I_RET,0);
  //  alginit = alg_createCopy(&asize);
  /*  sy_add("_AINIT", 0,1,0);
    puts("ALG INIT GENERATED:");
    alg_print(alginit, asize);*/
    return l;
}

void sy_generateMap(char *fbname){
    FILE *f;
    int i;
    char fname[150];
    char filename[500];

    sprintf(fname, "%s.map", fbname);
    pathjoin(filename, sy_output, fname);
    f = fopen(filename, "w");
    i = 0;
    while(symbols[i].i ==1)
    {
        fprintf(f, "%s:%d:%d,\n", symbols[i].name, symbols[i].pos, symbols[i].size);
        //printf("%10s %10d %10d\n", symbols[i].name, symbols[i].pos, symbols[i].size);
        i++;
    }
}

void sy_print()
{
    int i;
    printf("%10s %10s %10s\n", "name", "pos", "size");
    i = 0;
    while(symbols[i].i ==1)
    {
        printf("%10s %10d %10d\n", symbols[i].name, symbols[i].pos, symbols[i].size);
        i++;
    }
}


void sy_copyToDevice(char *fbname){
        int i;
        i = 0;
       // printf("FB: %s\n", fbname);
    while(symbols[i].i ==1)
    {
       // printf("%s %d\n",symbols[i].name, symbols[i].pos);
        if(symbols[i].isFunction == 0){
            dev_addVar(fbname, symbols[i].name, symbols[i].pos);

        }
        i++;
    }
}
