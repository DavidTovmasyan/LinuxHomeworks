#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

enum {BUF_SIZE = 64};

int main(int argc, char* argv[]){
	if(argc == 1){
		fprintf( stderr, "No args\n");
		exit(1);
	}
	char buf[BUF_SIZE];
	int n;
	int fd = open(argv[1], O_RDWR);
	if(fd == -1){
		perror("open");
		exit(2);
	}
	while ( (n = read(fd,buf,BUF_SIZE ) ) > 0){
		for(int i = 0;i<n;++i){
			if(isdigit(buf[i])){
				buf[i] = '_';
			}else
				buf[i] = toupper(buf[i]);
		}
		lseek(fd, -n, SEEK_CUR);
		write(fd, buf, n);
	}
	close(fd);
	return 0;
}
