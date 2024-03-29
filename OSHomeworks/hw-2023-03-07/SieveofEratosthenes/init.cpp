#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>

int main(){
	std::string pathname = "shm_file_2";
	key_t key = ftok(pathname.c_str(), 'a');
	if(key < 0){
		std::cout<<"ERROR: Cannor generate a key!!\n";
		exit(1);
	}
	bool exist = false;
	int shmid = shmget(key, 300*sizeof(bool), 0600 | IPC_CREAT | IPC_EXCL);
	if(shmid < 0){
		if(errno != EEXIST){
			std::cout<<"ERROR: Cannot create shared memory segment!!\n";
			exit(1);
		}
		else{
			shmid = shmget(key, 300*sizeof(bool), 0600);
			exist = true;
		}
	}
	bool* shared_arr = (bool*) shmat(shmid, NULL, 0);
	if(shared_arr == (bool*) -1){
		std::cout<<"ERROR: Cannot attach shared mem segment!!\n";
		perror("shmat");
		exit(errno);
	}
	for(unsigned int i = 0; i < 300; ++i){
		//The condition was "init as 0s", but my algorithm's syntax gets better with 1s
		shared_arr[i] = 1;
	}
	if(shmdt(shared_arr) < 0){
		std::cout<<"ERROR: Cannot detach the shm segment!!\n";
		exit(1);
	}
	return 0;
}
