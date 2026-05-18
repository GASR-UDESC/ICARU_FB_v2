
#ifndef _PILHA_H_
#define _PILHA_H_ 1

#define P_MAX 100

int valores[P_MAX];
int pos;

void pinit(){
	pos = 0;
}


void pinsert(int a){
	if(pos == P_MAX){
		puts("ERRO: Pilha Cheia em 'pilha.h'.");
		return;
	}
	valores[pos] = a;
	pos++;
}

int pget(){
	pos--;
	if(pos<0){
		printf("Erro na pilha('pilha.h')!\n");
		return 0;
	}
	return valores[pos];
}

#endif
