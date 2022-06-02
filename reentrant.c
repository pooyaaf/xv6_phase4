#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char *argv[])
{

        printf(1, "user: starting reentrant spinlock test ... \n");
        reentrant_spinlock_test();
        printf(1, "user: test completed ... \n");
        exit();
}