#include <signal.h>
#include <stdio.h>

int i = 0, j = 0;

void (*p_1)(int);
void (*p_2)(int);

void my_handler(int nsig)
{
    if (nsig == SIGINT)
    {
        printf("\nReceive signal %d, CTRL-C pressed\n", nsig);
        i++;
        if (i == 5)
            (void)signal(SIGINT, p_1);
    }
    if (nsig == SIGQUIT)
    {
        printf("\nReceive signal %d, CTRL-4 pressed\n", nsig);
        j++;
        if (j == 5)
            (void)signal(SIGQUIT, p_2);
    }
}

int main(void)
{

    p_1 = signal(SIGINT, my_handler);
    p_2 = signal(SIGQUIT, my_handler);
    while(1);
    return 0;
}