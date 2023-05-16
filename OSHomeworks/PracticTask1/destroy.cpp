#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>

int main() {
	std::string pathname = "shm_file";

	// create a key for shared mem
	key_t key = ftok(pathname.c_str(), 1);
	if(key < 0) {
		std::cout << "ERROR: Cannot generate a key!!\n";
		exit(errno);
	}
	int shmid = shmget(key, 0, 0);
	shmctl(shmid, IPC_RMID, NULL);
	std::cout<<"The shared memory has been removed succesfully!!\n";
	return 0;
}
