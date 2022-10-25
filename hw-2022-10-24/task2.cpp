#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

enum {BUFF_SIZE = 64};

int main(int argc, char* argv[]){
	if(strcmp(argv[1], "save") == 0 ){
		int x;
		int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if(fd == -1){
			perror(argv[2]);
			return 1;
		}
		while( scanf("%d", &x) != EOF ){
			write(fd, &x, sizeof(x));
		}
		close(fd);
	}
	else if(strcmp(argv[1], "print") == 0){
		int x;
		int fd = open(argv[2], O_RDONLY);
		if(fd  == -1){
			perror(argv[2]);
			return 1;
		}
		int n;
		while(n = read( fd, &x, sizeof(x) ) ){
			printf("%d\n", x);
		}
	}
	return 0;
}
