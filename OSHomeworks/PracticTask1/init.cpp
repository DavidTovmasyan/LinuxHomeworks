#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>
#include "bank_and_accounts.cpp"

int main(int argc, char* argv[]) {
	if(argc != 2){
		std::cout<<"Inapropriate number of arguments!!\n";
		exit(1);
	}
	std::string pathname = "shm_file";
	std::string num_str(argv[1]);
	int acc_num = std::stoi(num_str);
	// create a key for shared mem
	key_t key = ftok(pathname.c_str(), 1);
	if(key < 0) {
		std::cout << "ERROR: Cannot generate a key!!\n";
		exit(errno);
	}

	// create shared mem sement
	int shmid = shmget(key, sizeof(Bank), 0600 | IPC_CREAT | IPC_EXCL);
	if(shmid < 0) {
		if (errno != EEXIST) {
			std::cout << "ERROR: Cannot create shared mem segment!!\n";
			exit(1);
		}
		else {
			shmid = shmget(key, sizeof(bool), 0600);
		}
	}
	std::cout<<"The shared memory has been created succesfully!!\n";
	return 0;
}
