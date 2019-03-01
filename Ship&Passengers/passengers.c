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

    int result;
    int   semid;
    char pathname[]="ship.c";
    key_t key;
    struct sembuf mybuf;

    key = ftok(pathname, 0);

    if((semid = semget(key, 3, 0666 | IPC_CREAT)) < 0){
      printf("Can\'t create semaphore set\n");
      exit(-1);
    }

    /// The main cycle of passengers
    printf("\n\n");
    for (int i = 1; i <= NUMBER_OF_VOYAGES * BOAT_CAPACITY; i++){

    result = fork();

        if(result < 0) {
                printf("Can\'t fork child\n");
                exit(-1);
mybuf.sem_num = 0;
            mybuf.sem_op  = -1; /// D(S_1;1)
            mybuf.sem_flg = 0;

            if(semop(semid, &mybuf, 1) < 0){
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            printf("The %i passenger sat down!\n", i);

            mybuf.sem_num = 2;
            mybuf.sem_op  = 0; /// Z(S_3)
            mybuf.sem_flg = 0;

            if(semop(semid, &mybuf, 1) < 0){
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            mybuf.sem_num = 1;
            mybuf.sem_op  = -1; /// D(S_2;1)
            mybuf.sem_flg = 0;

            if(semop(semid, &mybuf, 1) < 0){
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            printf("The %i passenger came out!\n", i);

            return 0;
        } else if (result > 0) {
            /// Parent process
            /// Nothing
        } else {
            /// Child process

            mybuf.sem_num = 0;
            mybuf.sem_op  = -1; /// D(S_1;1)
            mybuf.sem_flg = 0;

            if(semop(semid, &mybuf, 1) < 0){
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            printf("The %i passenger sat down!\n", i);

            mybuf.sem_num = 2;
            mybuf.sem_op  = 0; /// Z(S_3)
            mybuf.sem_flg = 0;

            if(semop(semid, &mybuf, 1) < 0){
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            mybuf.sem_num = 1;
            mybuf.sem_op  = -1; /// D(S_2;1)
            mybuf.sem_flg = 0;

            if(semop(semid, &mybuf, 1) < 0){
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            printf("The %i passenger came out!\n", i);

            return 0;
        }
    }
    return 0;

}

