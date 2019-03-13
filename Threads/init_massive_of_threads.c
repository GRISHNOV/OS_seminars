#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy)

/*
 *   Parameter void *dummy is used only for type compatibility, and will not be used
 *   at the function now. At the same reason the return value of function has type 
 *   void *, but it wiil be not used at this program.
 */

{

    pthread_t mythid;

    mythid = pthread_self();

    a = a + 1;

    printf("Thread %lu, Calculation result = %d\n", mythid, a);

    return NULL;
}

int main()
{

    pthread_t mythid;
    pthread_t thid[5];
    int result[5];

    for (int i = 0; i < 5; i++)
    {
        result[i] = pthread_create(thid + i, (pthread_attr_t *)NULL, mythread, NULL);
        if (result[i] != 0)
        {
            printf("Error on thread_1 create, return value = %d\n", result[i]);
            exit(-1);
        }
    }

    mythid = pthread_self();

    a = a + 1;

    printf("Thread !MAIN!  %lu, Calculation result = %d\n", mythid, a);

    pthread_join(thid[0], (void **)NULL);
    pthread_join(thid[1], (void **)NULL);
    pthread_join(thid[2], (void **)NULL);
    pthread_join(thid[3], (void **)NULL);
    pthread_join(thid[4], (void **)NULL);

    return 0;
}
