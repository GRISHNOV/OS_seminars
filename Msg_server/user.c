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
      } info;
   } mybuf;

   /* Create or attach message queue */

   key = ftok(pathname, 0);

   if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
   {
      printf("Can\'t get msqid\n");
      exit(-1);
   }

   for (int i = 0; i < 5; i++)
   {

      result = fork();

      if (result < 0)
      {
         printf("FORK ERROR!\n");
         exit(0);
      }
      else if (result > 0)
      {
         //nothing
      }
      else
      {

         /* Send information */

         mybuf.mtype = 1;
         mybuf.info.PID = getpid();
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

         /*Waiting to receive a message from the server*/

         maxlen = 512;

         if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, mybuf.info.PID, 0)) < 0)
         {
            printf("Can\'t receive message from queue\n");
            exit(-1);
         }

         printf("I am IPD = %li. Message from server for me obtained! Server IPD = %i\n", mybuf.mtype, mybuf.info.PID);

         return 0;
      }
   }

   return 0;
}