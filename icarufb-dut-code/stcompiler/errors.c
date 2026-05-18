
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int line_counter;
char file[200];

void err_init(){
    line_counter = 0;
}

void err_lineInc(){
    line_counter++;
}
void err_lineReset(){
    line_counter = 0;
}
int err_getLine(){
    return line_counter;
}

void err_setFile(char *filename){
    strcpy(file, filename);
}

void err_printWarm(char *info){
    //printf("Warning: %s\n",info);
    printf("Warning ON LINE %d of FILE '%s':\n   %s\n",line_counter+1, file, info);
}
void err_printError(char *info){
    printf("Error: %s\n",info);
}
void err_printFatalError(char *info){
    printf("Error ON LINE %d of FILE '%s':\n   %s\n",line_counter+1, file, info);
    exit(1);
}
