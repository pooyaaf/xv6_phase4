#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

#define MUTEX 0
#define FULL 1
#define EMPTY 2

#define SIZE 5

void producer();
void consumer();

int main()
{
    sem_init(MUTEX, 1);
    sem_init(EMPTY, 5);
    sem_init(FULL, 0);

    int pid = fork();
    if (pid == 0)
    {
        wait();
        consumer();
    }
    else
    {
        int pid2 = fork();
        if (pid2 == 0)
        {
            producer();
        }
        else
        {
            wait();
        }
    }

    exit();

    return 0;
}

void producer()
{
    for (int j = 0; j < 4; j++)
    {
        sem_acquire(EMPTY);
        sem_acquire(MUTEX);

        printf(1, "Added to queue value :%d\n", j);

        sem_release(MUTEX);
        sem_release(FULL);
    }

    sem_acquire(MUTEX);

    printf(1, "Required products created successfully!\n");

    sem_release(MUTEX);

    exit();
}

void consumer()
{
    for (int j = 0; j < 10; j++)
    {
        sem_acquire(FULL);
        sem_acquire(MUTEX);
        // printf(1, "Consumed from queue value: %d\n", j);
        printf(1, "Counsumed from queue\n");
        sem_release(MUTEX);
        sem_release(EMPTY);
    }

    sem_acquire(MUTEX);

    printf(1, "Items consumed successfully!\n");

    sem_release(MUTEX);

    exit();
}