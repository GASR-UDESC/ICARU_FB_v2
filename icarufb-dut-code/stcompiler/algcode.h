

#ifndef _ALGCODE_H_
#define _ALGCODE_H_ 1

#include <string.h>

#include "instset.h"
#include "listadin.h"

struct alginst{
    char cmd;
    int par;
};

typedef struct alginst ALGINST;

void alg_init();
void alg_setOutput(char *output);
char *alg_getOutput();

void alg_gen(char cmd, int par);
void alg_reset();
int alg_newLabel();

void alg_backpath(int pos, int par);
void alg_backpathAll(LISTD *l, int label);
int alg_getNextPos();
ALGINST * alg_createCopy(int *size);

void alg_createAsmFile(char *name);
void alg_createHexFile(char *name);

void alg_selfPrint();
void alg_print(ALGINST * inst, int t);


#endif
