
#include "listadin.h"
#include <stdio.h>
#include <stdlib.h>

LISTD * listd_create()
{
    LISTD *l;
    l = (LISTD *)malloc(sizeof(LISTD));
    l->first = NULL;
    l->last = NULL;
    l->count = 0;
    return l;
}
int listd_append(LISTD *l, LISTD_DATA_TYPE data)
{
    LISTDE * e, * last;
    e = (LISTDE *)malloc(sizeof(LISTDE));
    if(e == NULL) return 0;
    e->prev = NULL;
    e->next = NULL;
    e->data = data;
    if(l->first == NULL)
    {
        l->first = e;
        l->last = e;
		l->count++;
    }
    else
    {



        last = l->first;
        while(last->next != NULL)
        {
            last = last->next;
        }
        last->next = e;
        l->last = e;
        e->prev = last;



		l->count++;
    }
    return 1;
}
int listd_insertFirst(LISTD *l, LISTD_DATA_TYPE data) {
    LISTDE * e, *first;
    e = (LISTDE *)malloc(sizeof(LISTDE));
    if(e == NULL) return 0;
    e->prev = NULL;
    e->next = NULL;
    e->data = data;

    first = l->first;
    l->first = e;
    e->next = first;
    first->prev = e;
	l->count++;
    return 1;

}
int listd_getIndex(LISTD *l, int index, LISTD_DATA_TYPE *e) {
    LISTDE * last;
    //printf("na linha: %d\n",err_getLine());
    if(l->count == 0)return 0;
    last = l->first;
    int c;
    c = 0;
    while(c < index)
    {
        last = last->next;
        if(last == NULL) return 0;
        c++;
    }
    *e = last->data;
    return 1;
}
int listd_removeIndex(LISTD *l, int index) {
    LISTDE * last, *prev, *next;
    last = l->first;
    int c;
    c = 0;
    if(l->count == 0){ return 0;}
    if(l->count == 1){
        free(l->first);
        l->first = NULL;
        l->last = NULL;
        //l->first = NULL;
        l->count--;
        return 1;
    }
    if(index == 0){
        last = l->first;
        l->first = l->first->next;
        l->first->prev = NULL;
        free(last);
        l->count--;
        return 1;
    }
    while(c < index)
    {
        last = last->next;
        if(last == NULL){  return 0;}
        c++;
    }
    prev = last->prev;
    next = last->next;


    if(prev != NULL)
        prev->next = next;
    if(next != NULL);
        next->prev = prev;
	l->count--;

    if(last!=NULL)
    free(last);

    return 1;
}
LISTD_DATA_TYPE listd_getLast(LISTD *l)
{
    return l->last->data;
}
LISTD_DATA_TYPE listd_getFirst(LISTD *l)
{
    return l->first->data;
}
int listd_isEmpty(LISTD *l)
{
    if(l->first == NULL)
    {
        return 1;
    }
    return 0;
}
int listd_push(LISTD *l, LISTD_DATA_TYPE data)
{
    return listd_append(l, data);
}
LISTD_DATA_TYPE listd_pop(LISTD *l) {
    LISTDE * last;
    if(listd_isEmpty(l)) return 0;
    last = l->last;
    last->prev->next = NULL;
	l->count--;
	if(l->count == 0){
        l->first = NULL;
	}
    return last->data;
}

void listd_merge(LISTD *r, LISTD *l1,LISTD *l2){
    int a, i;
    r = listd_create();
    i = 0;
    if(l1 != NULL)
    while(listd_getIndex(l1,i,&a)){
        listd_append(r,a);
        i++;
    }
    i=0;
    if(l2!=NULL)
    while(listd_getIndex(l2,i,&a)){
        listd_append(r,a);
        i++;
    }
}

void listd_print(LISTD *l, char *format)
{
    LISTDE * last;
    char form[10];
    int one;
	if(l == NULL){
		puts("(list null)\n");
		return;
	}
    last = l->first;
    printf("[");
    one = 1;
    while(last != NULL)
    {
        if(one)
        {
            sprintf(form,"%s", format);
            one = 0;
        }
        else
        {
            sprintf(form,", %s", format);
        }
        printf(form, last->data);
        last = last->next;
    }
    printf("]\n");
}

void listd_free(LISTD *l){
    LISTDE * last, *a;
    last = l->first;
    while(last != NULL)
    {
        a = last->next;
        free(last);
        last = a;
    }
    free(l);
}

