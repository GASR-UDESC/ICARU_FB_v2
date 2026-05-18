

#include "stack.h"

int stk_push(STACK *s, int val)
{
    if(s->p >= STACK_SIZE)
    {
        return 0;
    }
    s->data[s->p] = val;
    s->p++;
    return 1;
}
int stk_pop(STACK *s, int *val)
{
    if(s->p == 0)
    {
        return 0;
    }
    s->p--;
    *val = s->data[s->p];
    return 1;
}
int stk_init(STACK *s)
{
    s->p = 0;
    return 0;
}
