

#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_ 1

//#define TY_INT 1

typedef struct{
    char *name;
    int isFunction;
    int isEvt;
    int type;
    int pos;
    int size;
    int i;

    int init;
    int v_init;
    char *sv_init;
}SYMBOL;


void sy_setOutput(char *output);
void sy_init();
int sy_add(char *name, int type, int isFunction, int isEvt);
void sy_addi(char *name, int type, int isFunction, int isEvt, int init, int v_init, char *sv_init);
void sy_getEvtVars(int *start, int *count);
int sy_getPos(char *name);
int sy_getType(char *name);
int sy_getTotalSize();
int sy_generateInit();
void sy_generateMap(char *fbname);
void sy_print();

void sy_copyToDevice(char *fbname);

#endif
