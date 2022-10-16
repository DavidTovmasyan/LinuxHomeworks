#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int status;
	for(unsigned int i = 1;i<argc;++i){
		if(fork() == 0){
			execlp(argv[i],argv[i],NULL);
			return 127;
		}
		wait(&status);
		if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
			break;
		}
	}
	return 0;
}
