
#ifndef _ECC_H_
#define _ECC_H_ 1

#define ECC_MAX_STATES 500
#define ECC_MAX_TRANSITIONS 200

#include "algcode.h"

typedef struct{
    char *alg;
    char *evt;
    int i; //i = 0 means NULL
}ECC_ALG;

typedef struct{
    char *name;
    //char *algs[50];
    ECC_ALG algs[50];
    int num;
    int i; //i = 0 means NULL
}ECC_STATE;

typedef struct{
    char *from;
    char *to;
    ALGINST *inst;
    int inst_count;
    int i;
}ECC_TRANS;

void ecc_setOutput(char *output);
void ecc_genMap(char *name);
void ecc_init();
void ecc_addState(char *name);
void ecc_addAlg2State(char *stname, char *alg, char *evt);
int ecc_getInitialState();
int ecc_getLastState();
/** Will copy instructions from algcode and clear it. */
void ecc_addTrans(char *stfrom, char *stto);

/** Return the position of algorithm in instructions list */
int ecc_generate();

#endif // _ECC_H_


