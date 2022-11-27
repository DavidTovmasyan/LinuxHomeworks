#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int writtenBites;

void signalHandler(int sig){
	printf("Broken pipe!\n");
	printf("%d\n", writtenBites);
	exit(1);
}

int main(int argc, char* argv[]){
	int fd[2];
	signal(SIGPIPE, signalHandler);
	if(pipe(fd) == -1){
		perror(NULL);
		exit(127);
	}
	char str[] = "Hello world";
	if(fork() == 0){
		close(fd[0]);
		while(1)
			writtenBites += write(fd[1], str, strlen(str));
	}
	char buf[6];
	if(fork() == 0){
		close(fd[1]);
		read(fd[0], buf, 5);
		buf[5] = '\0';
		printf("%s\n", buf);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return 0;
}
