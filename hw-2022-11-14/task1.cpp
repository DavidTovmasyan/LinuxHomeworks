#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	if(argc < 5){
		fprintf( stderr, "Few args\n");
		exit(1);
	}
	int fdPipe[2];
	if( pipe(fdPipe) == -1){
		perror(NULL);
		exit(2);
	}
	if(fork() == 0){
		int fd1 = open(argv[2], O_RDONLY);
		if(fd1 == -1){
			perror(NULL);
			exit(2);
		}
		dup2(fd1, 0);
		dup2(fdPipe[1], 1);
		close(fd1);
		close(fdPipe[0]);
		close(fdPipe[1]);
		execlp(argv[1], argv[1], NULL);
		perror(NULL);
		exit(3);
	}
	if(fork() == 0){
		int fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if(fd2 == -1){
                        perror(NULL);
                        exit(2);
                }
		dup2(fd2, 1);
		dup2(fdPipe[0], 0);
		close(fd2);
		close(fdPipe[0]);
		close(fdPipe[1]);
		execlp(argv[3], argv[3], NULL);
		perror(NULL);
		exit(3);
	}
	wait(NULL);
	return 0;
}
