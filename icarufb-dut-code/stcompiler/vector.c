

#include "vector.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>



VECTOR * vec_create(int elSize){
    VECTOR *v;
    v = malloc(sizeof(VECTOR));
    v->next = 0;
    v->data = malloc(sizeof(void*));
    v->p = 0;
    v->elSize = elSize;
    return v;
}

int vec_add(VECTOR *v, void *element){
    void *e;
    v->p++;
    v->data = realloc(v->data, (v->p)*sizeof(void*) );
    e = malloc(v->elSize);
    memcpy(e, element, v->elSize);

    v->data[v->p-1] = e;
    return 1;
}

void * vec_getNext(VECTOR *v, void *element){
    void *p;
    if(v->p == 0) return NULL;
    if(v->next == v->p) return NULL;
    p= v->data[v->next];
    memcpy(element, p, v->elSize);
    v->next++;
    return p;
}
void vec_resetNext(VECTOR *v){
    v->next = 0;
}
int vec_get(VECTOR *v, void *s, int (*cmp)(void *, void *)){
    int i;
    i = 0;

    while(i < v->p){
        if(cmp(v->data[i], s)){
            return i;
        }
        i++;
    }
    return -1;
}

void *vec_getP(VECTOR *v, void *s, int (*cmp)(void *, void *)){
    int p;

    p = vec_get(v, s, cmp);
    if(p == -1) return NULL;
    return v->data[p];
}
void *vec_getLastP(VECTOR *v){
    return v->data[v->p-1];
}

int vec_getLastPointer(VECTOR *v){
    return v->p-1;
}

/** \todo Calculo CheckSum */
int vec_getCS(VECTOR *v){
    return 0;
}

void vec_print(VECTOR *v, void (*stPrint)(void *)){
    int i;
    i = 0;
    while(i < v->p){
        stPrint(v->data[i]);
        i++;
    }
}

int cmp(void * a, void * b){
    if(*(int*)a == *(int*)b) return 1;
    return 0;
}

void vec_test(){
    VECTOR *v;
    int a;

    v = vec_create(sizeof(int));
    a = 10;
    vec_add(v,&a );
    a = 20;
    vec_add(v,&a);
    a = 30;
    vec_add(v,&a);

    while(vec_getNext(v, &a) != NULL){
        printf("val: %d\n", a);
    }
    a = 20;
    printf("Index: %d\n", vec_get(v,&a, cmp));


}



