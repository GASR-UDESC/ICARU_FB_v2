
#ifndef _STACK_H_
#define _STACK_H_ 1

#define STACK_SIZE 30


struct stack{
    int data[STACK_SIZE];
    int p;
};

typedef struct stack STACK;

int stk_push(STACK *s, int val);
int stk_pop(STACK *s, int *val);
int stk_init(STACK *s);



#endif // _STACK_H_
