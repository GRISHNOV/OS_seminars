#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define BOAT_CAPACITY 3   /// N
#define NUMBER_OF_VOYAGES 2   /// k

int main(void){

    /// Initializing three semaphores (all 0)

    int   semid;
    char pathname[]="ship.c";
    key_t key;
    struct sembuf mybuf;

    key = ftok(pathname, 0);

    if((semid = semget(key, 3, 0666 | IPC_CREAT)) < 0){
      printf("Can\'t create semaphore set\n");
      exit(-1);
    }

    /// The main cycle of the boat

    for (int i = 1; i <= NUMBER_OF_VOYAGES; i++){

    printf("Start loading passengers\n");

    mybuf.sem_num = 2;
    mybuf.sem_op  = 1; /// A(S_3;1)
    mybuf.sem_flg = 0;

    if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
    }

    mybuf.sem_num = 0;
    mybuf.sem_op  = BOAT_CAPACITY; /// A(S_1;N)
    mybuf.sem_flg = 0;

    if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
    }

    mybuf.sem_num = 1;
    mybuf.sem_op  = BOAT_CAPACITY; /// A(S_2;N)
    mybuf.sem_flg = 0;

    if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
    }

    mybuf.sem_num = 0;
    mybuf.sem_op  = 0; /// Z(S_1)
    mybuf.sem_flg = 0;

    if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
    }

    printf("End of loading passengers\n");

    printf("Boat trip...\n");

    sleep(2);

    printf("The ship is approaching the pier...\n");

    printf("Start unloading passengers\n");

    mybuf.sem_num = 2;
    mybuf.sem_op  = -1; /// D(S_3;1)
    mybuf.sem_flg = 0;

    if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
    }

    mybuf.sem_num = 1;
    mybuf.sem_op  = 0; /// Z(S_2)
    mybuf.sem_flg = 0;

    if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1);
    }

    printf("End of unloading passengers\n");

    }

    return 0;

}

