/************************************************************************
    Copyright 2015 Leandro Israel Pinto
	
	This file is part of ICARU_FB.

    ICARU_FB is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ICARU_FB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ICARU_FB.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************/

#ifndef FILA_C
#define FILA_C 1


#define FC_ELEMENTS 10

struct filac{
	int e[FC_ELEMENTS];
	int i;
	int o;
};

typedef struct filac FILAC;


void fc_init(FILAC *f){
	f->i = 0;
	f->o = 0;
}

int fc_empty(FILAC *f){
	return f->i == f->o;
}

int fc_full(FILAC* f){
	if(f->i + 1 == f->o) return 1;
	if(f->i + 1 >= FC_ELEMENTS && f->o == 0) return 1;
	return 0;
}

int fc_inc(FILAC *f){
	if(fc_full(f)) return 0;
	f->i++;
	if(f->i >= FC_ELEMENTS){
		f->i = 0;
	}
	return 1;
}


int fc_add(FILAC *f, int e){
	printf("ADD: %d\n\r", e);
	if(fc_full(f)) return 0;
	f->e[f->i] = e;
	fc_inc(f);
	return 1;
}

int fc_get(FILAC *f){
	int e;
	if(fc_empty(f)) return -1;
	e = f->e[f->o];
	f->o++;
	if(f->o >= FC_ELEMENTS) f->o = 0;
	return e;
}
/*
void main(){
    FILAC f;
    fc_init(&f);

    fc_add(&f,10);
    fc_add(&f,20);

    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("-----\n");
    fc_add(&f,1);
    fc_add(&f,2);
    fc_add(&f,3);
    fc_add(&f,4);
    fc_add(&f,5);
    fc_add(&f,6);
    fc_add(&f,7);
    fc_add(&f,8);
    fc_add(&f,9);
    fc_add(&f,10);


    printf("%d\n", fc_get(&f));
    fc_add(&f,11);
    fc_add(&f,12);
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));
    printf("%d\n", fc_get(&f));


}
*/
#endif // FILA_C




