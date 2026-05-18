
#include "device.h"
#include "vector.h"
#include "errors.h"
#include <string.h>
#include <stdio.h>


VECTOR *func_blocks;


void dev_init()
{
    func_blocks = vec_create(sizeof(FUNC_BLOCK));
    dev_addfb("START");
    dev_addVar("START", "START", 0);
    dev_addVar("START", "COLD", 0);
}
void dev_addfb(char *name)
{
    FUNC_BLOCK f;
    f.name = strdup(name);
    printf("Criando %d...", (int)sizeof(FBVAR));
    f.vars = vec_create(sizeof(FBVAR));
    printf ("OK\n");
    vec_add(func_blocks, &f);

}
int dev_cmp(void *a, void *b)
{
    if(strcmp( ((FUNC_BLOCK*)a)->name, (char*)b) == 0)
    {
        return 1;
    }
    return 0;

}
void dev_addVar(char *name, char *var, int pos)
{
    FBVAR v;
    FUNC_BLOCK *f;
    v.name = strdup(var);
    v.pos = pos;

    if(strcmp(name,"-") == 0)
    {
        f = vec_getLastP(func_blocks);
    }
    else
    {
        f=vec_getP(func_blocks, name, &dev_cmp);
    }
    if(f == NULL)
    {
        err_printFatalError("F null");
    }
    vec_add(f->vars, &v);

}
int dev_cmpVar(void *v, void *var)
{
    if(strcmp( ((FBVAR*)v)->name, (char*)var) == 0)
    {
        return 1;
    }
    return 0;

}
int dev_getVarPos(char *var, char *fb)
{
    FBVAR *v;
    FUNC_BLOCK *f;
    f=vec_getP(func_blocks, fb, &dev_cmp);
    if(f == NULL)
    {
        printf("FB not founded: %s\n", fb);
        err_printFatalError("");
    }
    v = vec_getP(f->vars, var, &dev_cmpVar);
    if(v == NULL)
    {
        printf("Var %s not founded in FB %s\n",var, fb);
        err_printFatalError("");
    }
    return v->pos;
}




