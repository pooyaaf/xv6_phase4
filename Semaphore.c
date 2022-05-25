#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "Semaphore.h"

#define SEMAPHORE_COUNT 5

struct Semaphore semaphore[SEMAPHORE_COUNT];

void sem_init(uint i, uint v)
{
    semaphore[i].index = i;
    semaphore[i].capacity = v;
    initlock(&semaphore[i].lock, (char *)i);//semaphore -> name
    semaphore[i].first = semaphore[i].last = 0;
}

void sem_acquire(uint i)
{
    acquire(&semaphore[i].lock);
    while (semaphore[i].capacity == 0)
    {
        semaphore[i].procs[semaphore[i].last] = proc;
        semaphore[i].last = (semaphore[i].last + 1) % NPROC;
        sleep(proc, &semaphore[i].lock);
    }
    semaphore[i].capacity -= 1;
    release(&semaphore[i].lock);
}

void sem_release(uint i)
{
    acquire(&semaphore[i].lock);
    semaphore[i].capacity += 1;
    if (semaphore[i].procs[semaphore[i].first])
    {
        wakeup(semaphore[i].procs[semaphore[i].first]);
        semaphore[i].procs[semaphore[i].first] = 0;
        semaphore[i].first = (semaphore[i].first + 1) % NPROC;
    }
    release(&semaphore->lock);
}