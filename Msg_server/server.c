#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LAST_MESSAGE 255

int main(void)
{
    int msqid;
    char pathname[] = "server.c";
    key_t key;
    int i, len, maxlen, client_PID, server_PID;

    struct mymsgbuf
    {
        long mtype;
        //char mtext[81];
        struct
        {
            int PID;
            char mtext[256];
            float data;
        } info;
    } mybuf;

    key = ftok(pathname, 0);

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    printf("\n_____SERVER START WORK_____\n");

    while (1)
    {

        maxlen = 512;

        if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, -2, 0)) < 0)
        {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        if (mybuf.mtype == 2)
        {
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            exit(0);
        }

        client_PID = mybuf.info.PID;
        server_PID = getpid();

        printf("Obtained message from PID = %i\n", client_PID);

        /* Send information */

        mybuf.mtype = client_PID;
        mybuf.info.PID = server_PID;
        mybuf.info.data = mybuf.info.data * mybuf.info.data;
        sleep(1);
        //strcpy(mybuf.info.mtext, "This is client with PID = ");
        //len = strlen(mybuf.mtext)+1;
        len = sizeof(mybuf.info);
        //printf("%i\n",len);
        if (msgsnd(msqid, (struct msgbuf *)&mybuf, len, 0) < 0)
        {
            printf("1_Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            exit(-1);
        }

        printf("Sent messedge to PID = %i\n", client_PID);
    }

    return 0;
}
