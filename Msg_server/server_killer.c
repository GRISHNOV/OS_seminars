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
   int i, len, maxlen, result;

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

   /* Create or attach message queue */

   key = ftok(pathname, 0);

   if ((msqid = msgget(key, 0)) < 0)
   {
      printf("Can\'t get msqid\n");
      exit(-1);
   }

   /* Send information */

   mybuf.mtype = 2;
   mybuf.info.PID = getpid();
   //mybuf.info.data = 80 + rand() % 100 + i * 3;
   printf("I am IPD (KILLER) = %i\n", mybuf.info.PID);
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
   
   return 0;
}