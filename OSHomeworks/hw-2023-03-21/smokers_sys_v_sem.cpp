#include <iostream>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <string>
#include <stdlib.h>

#define TABACCO 0
#define MATCHES 1
#define PAPER 2
#define BARMEN_SEM 3

int sem_id;

void barmen(const std::string& inputs){

	std::cout << "Barmen is searching items..." << std::endl;


	for(auto ch : inputs){

		if(ch == 't'){
			struct sembuf found_tabacco{TABACCO, 1, 0};
			semop(sem_id, &found_tabacco, 1);
		}

		if(ch == 'p'){
			struct sembuf found_paper{PAPER, 1, 0};
			semop(sem_id, &found_paper, 1);
		}

		if(ch == 'm'){
			struct sembuf found_match{MATCHES, 1, 0};
			semop(sem_id, &found_match, 1);
		}
	}


	exit(0);
}

void smoker(int id){

	int needed_item = rand()%3;
	while(true){
		struct sembuf barmen_wait{BARMEN_SEM, -1, 0};
		semop(sem_id, &barmen_wait, 1);
		//if(semctl(sem_id, needed_item, GETVAL, 0) > 0){

		// barmen give the item
		struct sembuf item_recived{needed_item, -1, 0};
		semop(sem_id, &item_recived, 1);

		std::string using_item;
		if(needed_item == 0){
			using_item = "tabacco";
		}else if(needed_item == 1){
			using_item = "matches";
		}else{
			using_item = "papaer";
		}

		std::cout << "The process " << id << " is smoking using " << using_item <<std::endl;
		sleep(5);

		struct sembuf barmen_free{BARMEN_SEM, 1, 0};
                semop(sem_id, &barmen_free, 1);
		//}
	}
	exit(0);
}

int main(){

	// create semaphores
	sem_id = semget(IPC_PRIVATE, 4, IPC_CREAT | 0644);

	if(sem_id < 0){
		perror("error creating semaphores");
		exit(errno);
	}


	if(semctl(sem_id, TABACCO, SETVAL, 0) < 0){
		perror("tabacco semctl error");
		exit(errno);
	}
        if(semctl(sem_id, MATCHES, SETVAL, 0) < 0){
                perror("matches semctl error");
                exit(errno);
        }
        if(semctl(sem_id, PAPER, SETVAL, 0) < 0){
                perror("paper semctl error");
                exit(errno);
        }
        if(semctl(sem_id, BARMEN_SEM, SETVAL, 1) < 0){
                perror("barmen semctl error");
                exit(errno);
        }

	// make processes
	std::string inputs;
	std::cin >> inputs;
	int barmen_pid = fork();
	if(barmen_pid == 0){
		barmen(inputs);
	}

	int smokers_pid[3];

	for(int i = 0; i < 3; ++i){

		smokers_pid[i] = fork();
		if(smokers_pid[i] < 0){
			perror("fork error");
			exit(errno);
		}
		if(smokers_pid[i] == 0){
			smoker(i);
		}
	}
	return 0;
}
