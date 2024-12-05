#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#define N 100000
#define ALLTRIAL 10000

double GetRandom(double min, double max)
{
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

int main()
{
    struct timeval t0, t1;
    int N_left, N_right;
    int *N_state = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        N_state[i] = 0; // all left(=0)
    }
    double rand_i, rate;
    N_left = N;
    N_right = 0;
    srand((unsigned int)time(NULL));
    gettimeofday(&t0, NULL);

    for (int t = 0; t < ALLTRIAL; t++)
    {
        printf("trial: %d\n", t);
        for (int i = 0; i < N; i++)
        {
            rand_i = GetRandom(0, 1);
            rate = N_left / (double)N;
            if (rand_i <= rate)
            {
                N_state[i] = 1;
                N_left -= 1;
                N_right += 1;
            }
            else
            {
                N_state[i] = 0;
                N_left += 1;
                N_right -= 1;
            }
        }
    }
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);
    printf("run time: %ld.%06ld\n", t1.tv_sec, t1.tv_usec);

    return 0;
}
