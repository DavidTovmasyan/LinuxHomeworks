#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

enum{BUF_SIZE = 1024};

int main(int argc, char* argv[]){
	int fd = open(argv[1], O_RDONLY);
	char buf[BUF_SIZE];
	int i;
	int n;
	n = read(fd, buf, sizeof(buf));
	for(i=0;i<n;++i){
		if(buf[i] == ' ' || buf[i] == '\n'){
			buf[i] = '\0';
		}
	}
	close(fd);
	char* words[BUF_SIZE];
	words[0] = buf;
	int j = 1;
	for(i = 0; i < n - 1; ++i){
		if(buf[i] == '\0'){
			words[j] = &buf[i+1];
			++j;
		}
	}
	words[j] = NULL;

	char* args[j+1];
	args[0] = words[0];
	for(i = 1; i < j; ++i){
		args[i] = words[i+1];
	}
//for debug	printf("%s %s %s %s\n", args[0], args[1], args[2], args[3]);
	if(fork() == 0){
		int inputFd = open(words[1], O_RDONLY);
		dup2(inputFd, 0);
		close(inputFd);
		execvp(args[0], args);
		exit(1);
	}

	return 0;
}
