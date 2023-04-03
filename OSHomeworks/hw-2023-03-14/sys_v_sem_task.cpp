#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <iostream>
#include <sys/wait.h>
#include <string.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(EXIT_FAILURE);
}

int main(){
	key_t key;
    	int semid, semval;
    	struct sembuf semops;
    	union semun semarg;

    	// create a unique key for the semaphore set
    	if ((key = ftok(".", 'S')) == -1) {
        	error("ftok");
	}

    	// create a semaphore set with 1 semaphore
    	if ((semid = semget(key, 1, 0666 | IPC_CREAT)) == -1) {
        	error("semget");
    	}

    	// initialize the semaphore value to 0
    	semarg.val = 1;
     	if (semctl(semid, 0, SETVAL, semarg) == -1) {
        	error("semctl");
     	}

	//creating a shared memory
	int shm_id = shmget(5678, sizeof(int), IPC_CREAT | 0666);

	if(shm_id == -1){
		perror("Couldnt create the shm");
		exit(1);
	}

	int* shared_value = (int*) shmat(shm_id, NULL, 0);
	*shared_value = 0;
//	shmdt(shared_value);

	pid_t child1, child2;
	(child1 = fork()) && (child2 = fork());

	if(child1 == 0){
		int* shared_value = (int*) shmat(shm_id, NULL, 0);
		for(int i = 0;i<10000;++i){
			// acquire the semaphore
    			semops.sem_num = 0;
    			semops.sem_op = -1;
    			semops.sem_flg = 0;
    			if (semop(semid, &semops, 1) == -1) {
        			error("semop");
    			}
			//

			(*shared_value)++;

			// release the semaphore
    			semops.sem_num = 0;
    			semops.sem_op = 1;
    			semops.sem_flg = 0;
    			if (semop(semid, &semops, 1) == -1) {
        			error("semop");
    			}
			//
		}
		exit(0);
	}else if(child2 == 0){

		int* shared_value = (int*) shmat(shm_id, NULL, 0);
                for(int i = 0;i<10000;++i){
                        // acquire the semaphore
                        semops.sem_num = 0;
                        semops.sem_op = -1;
                        semops.sem_flg = 0;
                        if (semop(semid, &semops, 1) == -1) {
                                error("semop");
                        }
                        //

                        (*shared_value)++;

                        // release the semaphore
                        semops.sem_num = 0;
                        semops.sem_op = 1;
                        semops.sem_flg = 0;
                        if (semop(semid, &semops, 1) == -1) {
                                error("semop");
                        }
                        //
                }

		exit(0);
	}
	wait(NULL);
	wait(NULL);
	std::cout << *shared_value << std::endl;

	// remove the semaphore set
    	if (semctl(semid, 0, IPC_RMID, semarg) == -1) {
        	error("semctl");
    	}

	return 0;
}
