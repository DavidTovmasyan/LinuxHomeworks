#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int pid = getpid();
	printf("%d\n", pid);
	while(true){
		sleep(1);
	}
        return 0;
}
