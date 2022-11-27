#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int child;
	if( (child = fork()) == 0){
		execl("prog1", "prog1", NULL);
		exit(1);
	}
	int n;
	scanf("%d", &n);
	kill(child, n);
	int status;
	wait(&status);
	if(WIFSIGNALED(status)){
		printf("Signaled: %d\n", WTERMSIG(status));
	}
        return 0;
}
