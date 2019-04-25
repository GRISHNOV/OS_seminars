#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
//#include <math.h>

int i = 0, j = 0;
//int total_received = 0;

void (*p_0)(int);
void (*p_1)(int);

int data[32];

pid_t pid;

int step_of_2(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        int res = 1;
        for (int q = 0; q < n; q++)
        {
            res = res * 2;
            printf("LOL -> %i\n", res);
        }
        printf("FUNC_RES = %i\n", res);
        return res;
    }
}

void send_confirmation(pid_t pid)
{
    if (kill(pid, SIGUSR1) < 0)
    {
        printf("Error from kill() when sent SIGUSR1\n");
    }
    printf("Confirmation sent!\n");
}

void my_handler(int nsig)
{
    if (nsig == SIGUSR1)
    {
        printf("\nReceive signal SIGUSR1 = 0\n");
        data[i] = 0;
        i++;
        //total_received++;
        send_confirmation(pid);
        //printf("Received %i\n", total_received);
    }
    if (nsig == SIGUSR2)
    {
        printf("\nReceive signal SIGUSR2 = 1\n");
        data[i] = 1;
        i++;
        //total_received++;
        send_confirmation(pid);
        //printf("Received %i\n", total_received);
    }
}

int main(void)
{

    pid_t mypid = getpid();
    printf("myPID = %i\n", mypid);

    printf("PID for sending confirmation -> ");
    scanf("%i", &pid);
    printf("PID for sending confirmation = %i\n", pid);

    p_0 = signal(SIGUSR1, my_handler);
    p_1 = signal(SIGUSR2, my_handler);

    while (i != 32)
        ;

    int res = 0;

    printf("\n\n");
    for (int i = 0; i < 32; i++)
    {
        printf("%i", data[i]);
        if (data[i] == 1)
        {
            res = res + step_of_2(31 - i);
            printf("\nnow res = %i and step() = %i\n", res, step_of_2(i));
        }
    }
    printf("\n\nRESULT -> %i\n\n", res);

    return 0;
}
