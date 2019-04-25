#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int i = 0, j = 0;
int confirmation_amount = 0;

void (*p_0)(int);
//void (*p_1)(int);
int flag = 1;

void send_0(pid_t pid)
{
    if (kill(pid, SIGUSR1) < 0)
    {
        printf("Error from kill() when sent SIGUSR1\n");
    }
    else
    {
        printf("OK: Sent 0\n");
    }
}

void send_1(pid_t pid)
{
    if (kill(pid, SIGUSR2) < 0)
    {
        printf("Error from kill() when sent SIGUSR2\n");
    }
    else
    {
        printf("OK: Sent 1\n");
    }
}

void my_handler(int nsig)
{
    if (nsig == SIGUSR1)
    {
        printf("\nReceive signal SIGUSR1 as confirmation!\n");
        //confirmation_amount++;
        //printf("Total confirmation amount = %i\n\n", confirmation_amount);
        flag = 1;
    }
    /*if (nsig == SIGUSR2)
    {
        printf("\nReceive signal %d, SIGUSR2\n", nsig);
    }*/
}

int main(void)
{

    pid_t mypid = getpid();
    printf("myPID = %i\n", mypid);
    pid_t pid;
    printf("PID for sending data -> ");
    scanf("%i", &pid);
    printf("PID for sending data = %i\n", pid);

    int data;
    printf("Enter data -> ");
    scanf("%i", &data);
    printf("data = %i\n\n", data);

    p_0 = signal(SIGUSR1, my_handler);
    //p_1 = signal(SIGUSR2, my_handler);

    int arr[32];
    for (i = 31; i >= 0; i--)
    {
        arr[i] = (data >> i) % 2;
        if (arr[i] == 0)
        {
            flag = 0;
            send_0(pid);
            while (flag == 0 && confirmation_amount != 31)
                ;
        }
        if (arr[i] == 1)
        {
            flag = 0;
            send_1(pid);
            while (flag == 0 && confirmation_amount != 31)
                ;
        }
        //printf("%d", arr[i]);
    }

    //send_0(pid);
    //send_1(pid);

    sleep(1);

    return 0;
}
