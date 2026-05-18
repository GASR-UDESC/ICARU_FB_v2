

#ifndef _ASMLTAB_H_
#define _ASMLTAB_H_ 1


typedef struct altab{
    char label[500];
    int pos;
}ASMLTAB;



void asm_init();
void asm_addLabel(char *name, int pos);
void asm_addLabelCall(char *name, int pos);
void asm_backpath();

#endif // _ASMLTAB_H_
