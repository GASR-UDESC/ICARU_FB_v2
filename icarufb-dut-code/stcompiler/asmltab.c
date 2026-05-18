


#include "asmltab.h"
#include "vector.h"
#include "errors.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "listadin.h"
#include "algcode.h"

VECTOR *asmTable; //label e sua posicao no codigo
VECTOR *asmLabels; //posicoes de chamadas ao label



int asm_cmp(void *a, void *name)
{
    if(strcmp( ((ASMLTAB *)a)->label, (char *)name) == 0)
    {
        return 1;
    }
    return 0;
}

void asm_init()
{
    asmTable = vec_create(sizeof(ASMLTAB));
    asmLabels = vec_create(sizeof(ASMLTAB));
}

void asm_addLabel(char *name, int pos)
{
    ASMLTAB *a;
    a = malloc(sizeof(ASMLTAB));
    strcpy(a->label, name);
    a->pos = pos;
    vec_add(asmTable, a);
}

void asm_addLabelCall(char *name, int pos)
{
    ASMLTAB *a;
    a = malloc(sizeof(ASMLTAB));
    strcpy(a->label, name);
    a->pos = pos;
    vec_add(asmLabels, a);
}



int asm_getLabel(char *name)
{

    ASMLTAB *a;

    a = (ASMLTAB*)vec_getP(asmTable, name, &asm_cmp);
    if(a == NULL)
    {
        return -1;

    }
    return a->pos;
}

void asm_backpath()
{
    ASMLTAB a;
    int p;
    char er[1000];
    //vec_resetNext(asmLabels);
    while(vec_getNext(asmLabels, &a) != NULL)
    {
        p = asm_getLabel(a.label);
        if(p == -1)
        {
            sprintf(er, "Label %s not founded.", a.label);
            err_printFatalError(er);
        }
        alg_backpath(a.pos, p);
    }
}
