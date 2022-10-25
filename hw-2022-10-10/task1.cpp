#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	for(unsigned int i = 1; i < argc; ++i){
		if(fork()==0){
			execlp(argv[i],argv[i],NULL);
			return 0;
		}
		wait(NULL);
	}
	return 0;
}
