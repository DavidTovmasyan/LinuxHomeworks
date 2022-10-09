#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	for(unsigned int i = 0; i < argc; ++i){
		if(fork()==0){
			execlp(argv[i+1],argv[i+1],NULL);
			return 0;
		}
		wait(NULL);
	}
	return 0;
}
