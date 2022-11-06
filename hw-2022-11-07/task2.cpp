#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

enum{BUF_SIZE = 256};

int main(int argc, char* argv[]){
	int fd = open(argv[1], O_RDONLY);
	FILE *file = fdopen(fd, "r");
	char* words[20];
	int i = 0;
	int n;
	char buf[BUF_SIZE];
	while((n = read(fd, buf, BUF_SIZE)) > 0){
		while(fscanf(file, "%s", words[i]))
			++i;
	}
	close(fd);
	char* arguments[20];
	n = i;
	arguments[0] = words[0];
	for(i = 1;i<n-1;++i){
		arguments[i] = words[i+1];
	}
	if(fork() > 0){
		int inputFd = open(words[1], O_RDONLY);
		dup2(inputFd, 0);
		close(inputFd);
		execvp(arguments[0], arguments);
		exit(1);
	}
	return 0;
}
