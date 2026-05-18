
#include "ecc.h"
#include "errors.h"
#include "symbols.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "ospath.h"

ECC_STATE states[ECC_MAX_STATES];
ECC_TRANS transitions[ECC_MAX_TRANSITIONS];
int initial_state;
char ecc_output[10000];

void ecc_setOutput(char *output){
    strcpy(ecc_output, output);
}

void ecc_genMap(char *name){
    int i;
    int s;
    FILE *f;
    char filename[500];

    pathjoin(filename, ecc_output, name);
    f = fopen(filename, "w");
    s = ecc_getLastState() + 1;
    for(i=0;i<s;i++){
        fprintf(f,"%s:%d,\n", states[i].name,i);

    }
    fclose(f);
}

int ecc_getLastState()
{
    int j;
    j = 0;
    while(states[j].i == 1)
    {
        j++;
    }
    return j-1;
}

int ecc_getLastAlg(ECC_ALG *algs)
{
    int j;
    j = 0;
    while(algs[j].i == 1)
    {
        j++;
    }
    return j-1;
}
int ecc_getState(char *stname)
{
    int j;
    j = 0;
    if(states[j].i == 0)
    {
        printf("State '%s' undeclared\n", stname);
        err_printFatalError("");
    }
    while(strcmp(states[j].name,stname) != 0)
    {
        j++;
        if(states[j].i == 0)
        {
            printf("State '%s' undeclared\n", stname);
            err_printFatalError("");
        }
    }
    return j;
}


/* */
void ecc_init()
{
    int j;

    for(j = 0; j < ECC_MAX_STATES; j++)
    {
        states[j].i = 0;
        states[j].algs[0].i = 0;
    }
    for(j = 0; j < ECC_MAX_TRANSITIONS; j++)
    {
        transitions[j].i = 0;
    }
    initial_state = -1;
}

int ecc_getInitialState()
{
    if(initial_state < 0)
    {
        puts("Invalid initial state!!");
        exit(1);
    }
    return initial_state;
}

void ecc_addState(char *name)
{
    int j;
    j = ecc_getLastState()+1;
    states[j].name = strdup(name);
    states[j].i = 1;

}
void ecc_addAlg2State(char *stname, char *alg, char *evt)
{
    int j,k;
    if(strcmp(stname, "-") == 0)
    {
        j = ecc_getLastState();
    }
    else
    {
        j = ecc_getState(stname);
    }

    k = ecc_getLastAlg(states[j].algs);
    k++;
    if(alg == NULL){
        states[j].algs[k].alg = NULL;
    }else{
        states[j].algs[k].alg = strdup(alg);
    }
    states[j].algs[k].evt = strdup(evt);
    states[j].algs[k].i = 1;
    k++;
    states[j].algs[k].i = 0;

}

void ecc_addTrans(char *stfrom, char *stto)
{
    int t;
    //a = ecc_getState(stfrom);
    // b = ecc_getState(stto);
    t = 0;
    while(transitions[t].i == 1)
    {
        t++;
    }
    transitions[t].from = strdup(stfrom);
    transitions[t].to = strdup(stto);
    transitions[t].i = 1;

    transitions[t].inst = alg_createCopy(&transitions[t].inst_count);
    //printf("FROM %s to %s\n", stfrom, stto);
    //alg_print(transitions[t].inst,transitions[t].inst_count);
    alg_reset();
}

int ecc_generate()
{
    int s,a, t,l,l1,l2,le1,ic, /*evStart,evCount,*/ stval;
    STACK st;
    s = 0;

    l = alg_newLabel();
	/*while(states[s].i == 1)
    {
		if(strcmp(states[s].name, "START") == 0)
        {
            initial_state = s;
        }
		s++;
	}
	s=0;*/
    while(states[s].i == 1)
    {

		if(strcmp(states[s].name, "START") == 0)
        {
            initial_state = s;
        }

        alg_gen(I_LOAD, sy_getPos("__est"));
        alg_gen(I_CONST, s);
        alg_gen(I_IFEQ, alg_getNextPos()+2);                 //if(est == s)
        l1 = alg_newLabel();
        alg_gen(I_GOTO, 0);

        alg_gen(I_LOAD,  sy_getPos("__alg"));
        alg_gen(I_IF, alg_getNextPos()+2);
        l2 = alg_newLabel();
        alg_gen(I_GOTO, 0);
        alg_gen(I_CONST, 0);
        alg_gen(I_STORE, sy_getPos("__alg"));
        a = 0;
        while(states[s].algs[a].i == 1)
        {
            if(states[s].algs[a].alg != NULL && states[s].algs[a].evt != NULL)
            {
                alg_gen(I_CALL, sy_getPos(states[s].algs[a].alg));
                alg_gen(I_CONST, 1);
                alg_gen(I_STORE, sy_getPos(states[s].algs[a].evt));
            }
            if(states[s].algs[a].alg == NULL && states[s].algs[a].evt != NULL)
            {
                alg_gen(I_CONST, 1);
                alg_gen(I_STORE, sy_getPos(states[s].algs[a].evt));
            }
            if(states[s].algs[a].alg != NULL && states[s].algs[a].evt == NULL)
            {
                alg_gen(I_CALL, sy_getPos(states[s].algs[a].alg));
            }
            a++;
        }
        alg_backpath(l2, alg_getNextPos());
        t = 0;
        stk_init(&st);
        while(transitions[t].i == 1)
        {
            if(strcmp(transitions[t].from, states[s].name) == 0)
            {
                ic = 0;
                while(ic < transitions[t].inst_count)
                {
                    alg_gen(transitions[t].inst[ic].cmd, transitions[t].inst[ic].par);

                    ic++;
                }
                if(transitions[t].inst_count > 0)
                {
                    alg_gen(I_IF, alg_getNextPos()+2);
                    le1 = alg_newLabel();
                    alg_gen(I_GOTO, 0);
                    alg_gen(I_CONST, ecc_getState(transitions[t].to));
                    alg_gen(I_STORE, sy_getPos("__est"));
                    alg_gen(I_CONST, 1);//
                    alg_gen(I_STORE, sy_getPos("__alg"));//
                    //sy_getEvtVars(&evStart,&evCount);
                    //alg_gen(I_CLREVT, (evStart<<8) | evCount);

                    stk_push(&st, alg_getNextPos());

                    alg_gen(I_GOTO, 0);

                    alg_backpath(le1,alg_getNextPos());

                }

            }
            t++;
        }
        while(stk_pop(&st,&stval)){
            alg_backpath(stval, alg_getNextPos());
        }


        s++;
        alg_backpath(l1, alg_getNextPos());
    }
    alg_gen(I_RET,0);
    return l;
}

