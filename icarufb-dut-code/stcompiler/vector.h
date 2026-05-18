
#ifndef _VECTOR_H_
#define _VECTOR_H_ 1

typedef struct {
    void **data;
    int p;
    int next;
    int elSize;
} VECTOR;


VECTOR * vec_create(int elSize);
int vec_add(VECTOR *v, void *element);
void * vec_getNext(VECTOR *v, void *element);
void vec_resetNext(VECTOR *v);
int vec_get(VECTOR *v, void *s, int (*cmp)(void *, void *));
void *vec_getP(VECTOR *v, void *s, int (*cmp)(void *, void *));
void *vec_getLastP(VECTOR *v);
int vec_getLastPointer(VECTOR *v);
int vec_getCS(VECTOR *v);
void vec_print(VECTOR *v, void (*stPrint)(void *));
void vec_test();
#endif


