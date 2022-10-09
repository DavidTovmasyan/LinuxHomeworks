#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	char* arr[argc];
	for(unsigned int i = 0; i < argc-1; ++i){
		arr[i] = argv[i+1];
	}
	arr[argc-1] = NULL;
	if(fork() == 0){
		execvp(argv[1],arr);
		return 0;
	}
	wait(NULL);
	printf("\nFinish\n");
	return 0;
}
