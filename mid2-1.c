#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>

int main()
{
    // initial
    int N = 100000;
    // time
    struct timeval t0, t1;
    gettimeofday(&t0, NULL);
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
    printf("runtime: %ld.%06ld\n", t1.tv_sec, t1.tv_usec);
    return 0;
}
