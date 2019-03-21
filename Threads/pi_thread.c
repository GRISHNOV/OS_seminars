#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

double a = 0;
int N = 0;
double h = 0;

double f(double x)
{
    return sqrt(4 - x * x);
}

struct Param
{
    float x_start;
    float x_end;
};

void *mythread(struct Param *arg)
{

    pthread_t mythid;

    mythid = pthread_self();

    double S = 0;
    double dx = h;

    for (double i = arg->x_start; i <= arg->x_end - dx; i = i + dx)
    {
        S = S + dx * 0.5 * (f(i) + f(i + dx));
    }

    printf("Thread %lu, Calculation result = %lf\n", mythid, S);
    a = a + S;
    return NULL;
}

int main()
{

    printf("h:");
    scanf("%lf", &h);
    if (h > 2 || h <= 0)
    {
        printf("h mast be <= 2.0 and h > 0\n");
        exit(0);
    }
    printf("N:");
    scanf("%i", &N);

    double elem_pat = 2.0 / h;
    printf("elem_pat = %lf\n", elem_pat);
    int elem_pat_int = (int)elem_pat;
    if (elem_pat_int < N)
    {
        printf("Attention! Given h and N, there are threads that has not work! Take a smaller h or a smaller N!\n");
        exit(0);
    }
    if (N <= 0)
    {
        printf("N mast be >= 0!!!\n");
        exit(0);
    }
    printf("elem_pat_int = %d\n", elem_pat_int);
    double *integ_point = (double *)malloc(elem_pat_int * sizeof(double));
    for (int i = 0; i < elem_pat_int; i++)
    {
        integ_point[i] = h * i;
        printf("%i integ point = %lf\n", i, integ_point[i]);
    }

    printf("\n");
    sleep(2);

    int elem_work = elem_pat_int / N;
    printf("elem_work = %i\n", elem_work);
    double *start_integ_point = (double *)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++)
    {
        start_integ_point[i] = integ_point[i * elem_work];
        printf("start_integ_point for thread %i = %lf\n", i, start_integ_point[i]);
    }

    sleep(2);
    printf("\n");
    struct Param *args_array = (struct Param *)malloc(N * sizeof(struct Param));

    for (int i = 0; i < N; i++)
    {
        args_array->x_start = start_integ_point[i];
        if (i != N - 1)
        {
            args_array->x_end = start_integ_point[i + 1];
        }
        else
        {
            args_array->x_end = 2.0;
        }
        printf("for thread %i\n", i);
        printf("start_x = %lf\n", args_array->x_start);
        printf("end_x = %lf\n\n", args_array->x_end);
        args_array++;
    }
    args_array = args_array - N;

    sleep(4);
    printf("\n");

    pthread_t mythid;
    pthread_t *thid = (pthread_t *)malloc(N * sizeof(pthread_t));
    int *result = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
    {
        result[i] = pthread_create(thid + i, (pthread_attr_t *)NULL, mythread, args_array + i);
        if (result[i] != 0)
        {
            printf("Error on thread_1 create, return value = %d\n", result[i]);
            exit(-1);
        }
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(thid[i], (void **)NULL);
    }

    printf("\nPI ~ %lf\n\n", a);

    free(integ_point);
    free(start_integ_point);
    free(args_array);
    free(thid);
    free(result);
    return 0;
}
