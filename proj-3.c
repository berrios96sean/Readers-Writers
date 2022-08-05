#include "sem.h"
#include "threads.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int r = 0;
int w = 0;
int readWaitCount = 0;
int readCount = 0;
int writeWaitCount = 0;
int writeCount = 0; 
int i = 0;

Semaphore *rsem, *wsem;

void reader(int readerID);
void reader_entry();
void reader_exit();
void writer(int writerID);
void writer_entry();
void writer_exit();

void reader(int readerID)
{
    reader_entry();
    printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
    yield();
    printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i);
    reader_exit();
    TCB_t *current = DelQueue(&RunQ);

    if (RunQ == NULL) {
        exit(0);
    }

    swapcontext(&(current->context), &(RunQ->context));
}

void reader_entry()
{
    if (writeWaitCount > 0 || writeCount > 0)
    {
        readWaitCount++;
        P(rsem);
        readWaitCount--;
    }
    readCount++;
}
void reader_exit()
{
    readCount--;
    if (readCount == 0 && writeWaitCount > 0)
    {
        V(wsem);
    }
}
void writer(int writerID)
{
    writer_entry();
    i = -writerID;
    printf("\n This is the %d th writer writing value i = %d \n",
           -writerID, i);
    yield();
    printf("\n This is the %d th writer verifying value i = %d \n",
           -writerID, i);
    writer_exit();
    TCB_t *current = DelQueue(&RunQ);
    if (RunQ == NULL)
    {
        exit(0);
    }
    swapcontext(&(current->context), &(RunQ->context));
}
void writer_entry()
{
    if (readCount > 0 || writeCount > 0 || readWaitCount > 0 || writeWaitCount > 0)
    {
        writeWaitCount++;
        P(wsem);
        writeWaitCount--;
    }
    writeCount++;
}
void writer_exit()
{
    writeCount--;
    if (readWaitCount > 0)
    {
        for (int i = 0; i < readWaitCount; i++)
        {
            V(rsem);
        }
    }
    else if (writeWaitCount > 0)
    {
        V(wsem);
    }
}


void main(char **args)
{
    rsem = malloc(sizeof(Semaphore));
    wsem = malloc(sizeof(Semaphore));
    initSem(rsem, 0);
    initSem(wsem, 0);
    InitQueue(&RunQ);
    scanf("%d,%d", &r, &w);
    for (int i = 0; i < r + w; i++)
    {
        int id;
        scanf("%d", &id);
        if (id > 0)
        {
            start_thread(reader, id);
        }
        else if (id < 0)
        {
            start_thread(writer, id);
        }
    }
    run();
}

