#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

enum {BUFF_SIZE = 256};

int main(int argc, char* argv[]){
	int fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1){
		perror(argv[1]);
		return 1;
	}
	char ourBuff[256];
	int n;
	int fd2 =  open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(fd2 == -1){
		perror(argv[2]);
		return 1;
	}
	while((n = read(fd1, ourBuff, BUFF_SIZE)) > 0){
		for(unsigned int i = 0; i < n;++i){
			if(isdigit(ourBuff[i]))
				ourBuff[i] = 'X';
		}
		write(fd2, ourBuff, n);
	}
	close(fd1);
	close(fd2);
	return 0;
}
