#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>

bool isPrime(int x){
	if(x <= 1){
		return false;
	}
	for(unsigned int i = 2;i < x; ++i){
		if(x % i == 0){
			return false;
		}
	}
	return true;
}

int main(){
	std::string pathname = "shm_file_1";
	//creating a key for shared memory
	key_t key = ftok(pathname.c_str(), 'a');
	if(key < 0){
		std::cout<<"ERROR: Cannot generate a key!!\n";
		exit(1);
	}
	bool exist = false;
	//creating shared memory segment
	int shmid = shmget(key, sizeof(bool), 0600 | IPC_CREAT |IPC_EXCL);
	if(shmid < 0){
		if(errno != EEXIST){
			std::cout<<"ERROR: Cannot create shared memory segment!!\n";
			exit(1);
		}
		else{
			shmid = shmget(key, sizeof(bool), 0600);
			exist = true;
		}
	}
	//write from shm
	bool* shared_bool = (bool*) shmat(shmid, NULL, 0);
	if(shared_bool == (bool*) -1){
		std::cout<<"ERROR: Cannot attach shared mem segment!!\n";
		perror("shmat");
		exit(errno);
	}
	int x;
	std::cin>>x;
	*shared_bool = isPrime(x);
	std::cout<<"You have written the number: "<<x<<std::endl;
	//detach the shm segment
	if(shmdt(shared_bool) < 0){
		std::cout<< "ERROR: Cannot detach the shm segment!!\n";
		exit(1);
	}
	return 0;
}
