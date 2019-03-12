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
    pthread_t thid_1, thid_2, mythid;
    int result_1, result_2;

    result_1 = pthread_create(&thid_1, (pthread_attr_t *)NULL, mythread, NULL);
    //result_2 = pthread_create(&thid, (pthread_attr_t *)NULL, mythread, NULL);

    if (result_1 != 0)
    {
        printf("Error on thread_1 create, return value = %d\n", result_1);
        exit(-1);
    }

    printf("Thread created, thid = %lu\n", thid_1);

    result_2 = pthread_create(&thid_2, (pthread_attr_t *)NULL, mythread, NULL);

    if (result_1 != 0)
    {
        printf("Error on thread_2 create, return value = %d\n", result_2);
        exit(-1);
    }

    printf("Thread created, thid = %lu\n", thid_2);

    mythid = pthread_self();

    a = a + 1;

    printf("Thread %lu, Calculation result = %d\n", mythid, a);

    pthread_join(thid_1, (void **)NULL);
    pthread_join(thid_2, (void **)NULL);

    return 0;
}
