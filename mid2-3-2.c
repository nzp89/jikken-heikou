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
FILE *fp;

void *thread(void *args)
{
    int start = *((int *)args); // 開始番号
    int end = start + N / 2;    // 終了番号
    struct timeval t1;

    for (int i = start; i < end; i++)
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
    fprintf(fp, "sub-thread runtime: %ld.%06ld\n", t1.tv_sec, t1.tv_usec);
    return NULL;
}

int main()
{
    // 初期化
    gettimeofday(&t0, NULL);
    fp = fopen("output.txt", "w");

    // 2つのスレッドを作成
    pthread_t th1, th2;
    int start1 = 1, start2 = N / 2;

    pthread_create(&th1, NULL, thread, (void *)&start1);
    pthread_create(&th2, NULL, thread, (void *)&start2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    // 終了時間
    struct timeval t2;
    gettimeofday(&t2, NULL);
    timersub(&t2, &t0, &t2);
    fprintf(fp, "main-thread runtime: %ld.%06ld\n", t2.tv_sec, t2.tv_usec);

    return 0;
}
