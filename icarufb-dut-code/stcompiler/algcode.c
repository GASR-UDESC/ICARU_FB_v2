
#include "algcode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listadin.h"
#include "ospath.h"


#ifdef ALG_CUSTOM
#include "listadin.c"
#include "instset.c"
int main(int argc, char **argv){
    alg_init();
	/* Create the DELAY block */
	alg_gen(I_RET, 0);
	alg_gen(I_ARLOAD, 100);


	/* Create the START block */
	/*
    alg_gen(I_RET, 0);
    alg_gen(I_ALLOC, 5);
    alg_gen(I_CONST, 1);
    alg_gen(I_STORE, 0);
    alg_gen(I_RET, 0);
    alg_createAsmFile("START.asm");
    alg_createHexFile("START.hex");
	*/
    return 0;
}
#endif


ALGINST algInst[50000];
int alg_pointer;
char alg_output[10000];

void alg_setOutput(char *output){
    strcpy(alg_output, output);
}
char *alg_getOutput(){
    return alg_output;
}


void alg_init(){
    alg_pointer = 0;
    sprintf(alg_output, "  ");
}

void alg_gen(char cmd, int par){

    algInst[alg_pointer].cmd = cmd;
    algInst[alg_pointer].par = par;
    alg_pointer++;
}

void alg_reset(){
    alg_pointer = 0;
}

int alg_newLabel(){
    return alg_pointer;
}

void alg_backpath(int pos, int par){
    algInst[pos].par = par;
}

void alg_backpathAll(LISTD *l, int label){
    int a;
    if(l==NULL) return;
    while(listd_getIndex(l,0,&a)){
        alg_backpath(a,label);
        listd_removeIndex(l,0);
    }
}

int alg_getNextPos(){
    return alg_pointer;
}


ALGINST * alg_createCopy(int *size){
     ALGINST * alg;

     alg = malloc(sizeof(ALGINST) * alg_pointer);
     *size = alg_pointer;
     memcpy(alg, algInst, sizeof(ALGINST) * alg_pointer);
     /*
     i = 0;
     while(i < alg_pointer){
        memcpy(alg, &algInst[i], sizeof(ALGINST));
        i++;
     }
     */
     return alg;
}

void alg_createAsmFile(char *name){
    FILE *f;
    char filename[500];
    int i;
    char str[20];
//    char filename[200];

    //sprintf(filename, "%s/%s", alg_output, name);
	//printf("Generating %s\n", filename);
	pathjoin(filename, alg_output, name);
    f = fopen(filename, "w");

    //f = fopen(name, "w");
    i=0;
    fprintf(f,";File Asm: %s\n", name);
    while(i < alg_pointer){
        fprintf(f,"\t%5d: %-10s %3d, %3d (%5d = %4Xh)\n", i,instText(algInst[i].cmd,str), algInst[i].par >> 8, algInst[i].par & 0xFF, algInst[i].par, algInst[i].par);
        i++;
    }
}
void alg_createHexFile(char *name){
    FILE *f;
    char filename[500];
    int i;

   // sprintf(filename, "%s/%s", alg_output, name);
   pathjoin(filename, alg_output, name);
    f = fopen(filename, "w");
   // f = fopen(name, "w");
    i=0;
   // fprintf(f,";File Hex: %s\n", name);
    while(i < alg_pointer){
        fprintf(f,"%03d %03d %03d ",  algInst[i].cmd, (algInst[i].par >> 8)&0xFF , algInst[i].par & 0xFF);
        i++;
       /* if(i%8 == 0){
            fprintf(f, "\n");

        }*/
    }
}

void alg_print(ALGINST * inst, int t){
    int i;
    char str[20];
    i=0;
    printf("\tALG_________\n");
    while(i < t){
        printf("\t%5d: %-10s %5d\n", i, instText(inst[i].cmd,str), inst[i].par);
        i++;
    }
}

void alg_selfPrint(){
    alg_print(algInst,alg_pointer);
}

int alg_getId(ALGINST * inst, int t){
    int i;
    int id;
    id = 0;
    for(i = 0; i < t; i++){
          id = id + inst[i].cmd + inst[i].par;
    }
    return id;
}
int alg_getSelfId(){
 return alg_getId(algInst, alg_pointer);
}



