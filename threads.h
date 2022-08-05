#ifndef THREADS_H
#define THREADS_H
#include "q.h"
TCB_t *RunQ;
void start_thread(void (*function)(int), int id)
{
    void *stack = (void *)malloc(8192);
    TCB_t *tcb = NewItem();
    init_TCB(tcb, function, stack, 8192, id);
    AddQueue(&RunQ, tcb);
}
void run()
{
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &(RunQ->context));
}

void yield()
{
    ucontext_t from, to;
    getcontext(&from);
    RunQ->context = from;
    RotateQ(&RunQ);

    to = RunQ->context;
    if (RunQ->next != RunQ)
    {
        swapcontext(&(RunQ->prev->context), &to);
    }
}
#endif
