
#ifndef _ATRIBUTOS_H_
#define _ATRIBUTOS_H_ 1

#define TY_INT  1
#define TY_BYTE 2
#define TY_REAL 3
#define TY_BOOL 2


#include "listadin.h"
struct atributos{
	int intval;
	float floatval;
	char * str;
	int isInit;
	int auxInt;

	int size;
	int type;

	LISTD *listav;
	LISTD *listaf;
	int label;
};

typedef struct atributos ATRIBUTOS;

#endif


