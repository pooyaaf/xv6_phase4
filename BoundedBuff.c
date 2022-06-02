#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

#define MUTEX 11
#define EMPTY 12
#define FULL 13
#define SIZE 5

void producer()
{
    int step1 = 0;int step2 =10;
    while (step1 < SIZE)
    {
        sem_acquire(step1);
        sem_acquire(MUTEX);
        step1++;
        printf(1, "Produced some value %d\n");

        sem_release(MUTEX);
        // printf(1, "Full queue.\n");
        step2--;
        sem_release(step2);
    }
}
void consumer()
{

    for (int j = 0; j < 5; j++)
    {
        sem_acquire(FULL);
        sem_acquire(MUTEX);

        printf(1, "Consume value %d\n", j);

        for (int i = 0; i < 200; i++)
            if (i % 50 == 0)
                printf(1, "Consumed some value %d\n", i);

        printf(1, "Empty queue.\n");

        sem_release(MUTEX);
        sem_release(EMPTY);
    }
}
void PRO_CONS(int activity)
{
    producer();
    // consumer():

    exit();
}

int main()
{
    sem_init(MUTEX, 1);
    for (int i = 0; i < SIZE * 2; i++)
    {
        sem_init(i, 1);
    }
    // putting initial value producer Empty
    for (int i = SIZE; i < SIZE * 2; i++)
    {
        sem_acquire(i);
    }
    for (int i = 0; i < SIZE; i++)
    {
        int id = fork();
        if (!id)
            PRO_CONS(i + 1);
    }
    exit();
}