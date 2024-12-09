#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <err.h>
#include <errno.h>

int N = 100000;
struct timeval t0;

void *thread(void *args)
{
    struct timeval t1;
    for (int i = 1; i < N; i++)
    {
        int sum_yakusu = 0;
        for (int j = 1; j < i; j++)
        {
            if (i % j == 0)
            {
                sum_yakusu += j;
            }
        }
        if (sum_yakusu == i)
        {
            printf("perfect number: %d\n", i);
        }
    }
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);
    printf("sub-thread runtime: %ld.%06ld\n", t1.tv_sec, t1.tv_usec);
    return NULL;
}

int main()
{
    // initial
    gettimeofday(&t0, NULL);
    // create thread
    pthread_t th;
    pthread_create(&th, NULL, thread, (void *)NULL);
    pthread_join(th, NULL);
    // time
    struct timeval t2;
    gettimeofday(&t2, NULL);
    timersub(&t2, &t0, &t2);
    printf("main-thread runtime: %ld.%06ld\n", t2.tv_sec, t2.tv_usec);
    return 0;
}
