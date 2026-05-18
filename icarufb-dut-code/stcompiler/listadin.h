/*

	Lista Dinamica
	==============
    Este codigo e fornecido da forma em que se encontra,
    sem garantias. A utilizacao do mesmo e de responsabilidade
    do proprio utilizador.


    Exemplo de uso:
    ===============
    LISTD *list;
    list = listd_create();
    listd_append(list, 50);

    Exemplo de uso como uma pilha:
    ==============================
    LISTD *list;
    list = listd_create();
    listd_push(list, 100); //push
    a = listd_pop(list);   //pop

    Exemplo de uso como uma fila:
    =============================
    LISTD *list;
    list = listd_create();
    listd_insertFirst(list, 50); //insere no inicio
    a = listd_pop(list);         //remove do final

*/

#ifndef _LISTADIN_H_
#define _LISTADIN_H_ 1


/** Utilize LISTD_DATA_TYPE para definir o tipo
  * dos dados na lista.
  * Ex.: #define LISTD_DATA_TYPE float
  *
  * O padrao sera 'int'.
  */
#ifndef LISTD_DATA_TYPE
#define LISTD_DATA_TYPE int
#endif

struct listdElement{
	LISTD_DATA_TYPE data;
	struct listdElement *next;
	struct listdElement *prev;
};
typedef struct listdElement LISTDE;

struct listdin{
	int count;
	LISTDE * first;
	LISTDE * last;
};
typedef struct listdin LISTD;

/** Cria uma lista.
  * Retorna NULL em caso de falha.
  */
LISTD * listd_create();

/** Acrescenta 'data' ao final da lista.
  * Retorna 1 se sucesso,
  * 0 em caso de falha.
  */
int listd_append(LISTD *l, LISTD_DATA_TYPE data);

/** Acrescenta 'data' no inicio da lista.
  * Retorna 1 se sucesso,
  * 0 em caso de falha.
  */
int listd_insertFirst(LISTD *l, LISTD_DATA_TYPE data);

/** Coloca o elemento da posicao 'index' da lista em *e */
int listd_getIndex(LISTD *l, int index, LISTD_DATA_TYPE *e);

/** Remove o elemento da posicao 'index' da lista.
  * Retorna 1 se sucesso,
  * 0 em caso de falha.
  */
int listd_removeIndex(LISTD *l, int index);

/** Retorna o ultimo elemento da lista. */
LISTD_DATA_TYPE listd_getLast(LISTD *l);

/** Retorna o primeiro elemento da lista. */
LISTD_DATA_TYPE listd_getFirst(LISTD *l);

/** Verifica se a lista esta vazia.
 *  Retorna 1 se a lista estiver vazia
 *  caso contrário retorna 0.
 */
int listd_isEmpty(LISTD *l);

/** Acrescenta 'data' ao final da lista.
  * Retorna 1 se sucesso,
  * 0 em caso de falha.
  */
int listd_push(LISTD *l, LISTD_DATA_TYPE data);

/** Retorna o ultimo elemento removendo-o da lista. */
LISTD_DATA_TYPE listd_pop(LISTD *l);


void listd_merge(LISTD *r, LISTD *l1,LISTD *l2);

/** Imprime os elementos da lista no modelo [e1, e1, ...]
 *  'format' informa como os dados devem ser impresso,
 *  mesmo padrao da funcao printf.
 *  Ex.:
 *  Para imprimir uma lista de inteiros: listd_print(list, "%d");
 */
void listd_print(LISTD *l, char *format);

/** Destroi a lista. */
void listd_free(LISTD *l);

#endif



