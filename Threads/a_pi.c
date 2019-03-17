#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEP 0.00001
#define STEP_ITERATION 2000000000

//int S = 0;
//double rez = 0;

double f(double x)
{
    return (1 / ((x + 1) * sqrt(x)));
}

void *mythread(void *dummy)
{

    pthread_t mythid;
    mythid = pthread_self();
    printf("Thread %lu, Calculation init!\n", mythid);

    double step = STEP;
    double x_i = step;
    double y_i = f(x_i);
    double y_i_old;
    double S = 0;
    for (int i = 1; i < STEP_ITERATION / 4; i++)
    {
        x_i = x_i + step;
        y_i_old = y_i;
        y_i = f(x_i);
        S = S + (y_i + y_i_old) * step * 0.5;
    }
    printf("%f\n", S);
    printf("%f <i_last> with %f <step>\n", x_i, STEP);
    //rez = rez + S;

    return NULL;
}

int main()
{

    pthread_t mythid;
    pthread_t thid[5];
    int result[5];

    for (int i = 1; i <= 4; i++)
    {
        result[i] = pthread_create(thid + i, (pthread_attr_t *)NULL, mythread, NULL);
        if (result[i] != 0)
        {
            printf("Error on thread_1 create, return value = %d\n", result[i]);
            exit(-1);
        }
    }

    mythid = pthread_self();

    printf("Thread !MAIN!  %lu\n", mythid);

    pthread_join(thid[0], (void **)NULL);
    pthread_join(thid[1], (void **)NULL);
    pthread_join(thid[2], (void **)NULL);
    pthread_join(thid[3], (void **)NULL);
    pthread_join(thid[4], (void **)NULL);

    //printf("REZ = %f\n", rez);

    return 0;
}
