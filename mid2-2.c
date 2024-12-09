#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>

int main()
{
    // initial
    int N = 100000;
    int n_pro = 4;
    int range = N / n_pro;
    printf("range = %d\n", range);
    FILE *fp = fopen("output.txt", "w");
    // time
    struct timeval t0, t1;
    gettimeofday(&t0, NULL);
    // fork
    pid_t pid[n_pro];
    for (int j = 0; j < n_pro; j++)
    {
        pid[j] = fork();
        if (-1 == pid[j])
        {
            err(EXIT_FAILURE, "cannot create");
        }
        else if (0 == pid[j])
        {
            // child process
            struct timeval t_start, t_end;
            gettimeofday(&t_start, NULL);
            // printf("child %d\n", j);

            for (int i = j * range + 1; i < (j + 1) * range; i++)
            {
                int sum_yakusu = 0;
                for (int k = 1; k < i; k++)
                {
                    if (i % k == 0)
                    {
                        sum_yakusu += k;
                    }
                }
                if (sum_yakusu == i)
                {
                    printf("perfect number: %d\n", i);
                }
            }
            gettimeofday(&t_end, NULL);
            timersub(&t_end, &t_start, &t_end);
            fprintf(fp, "child %d runtime: %ld.%06ld\n", j, t_end.tv_sec, t_end.tv_usec);
            exit(EXIT_SUCCESS);
        }
    }
    // Parent waits for all child processes to finish
    for (int j = 0; j < n_pro; j++)
    {
        wait(NULL); // Wait for each child to finish
    }
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);
    fprintf(fp, "all runtime: %ld.%06ld\n", t1.tv_sec, t1.tv_usec);
    exit(EXIT_SUCCESS);
    return 0;
}
