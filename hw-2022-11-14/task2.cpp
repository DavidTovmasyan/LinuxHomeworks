#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int fdPipe[2];
	if(pipe(fdPipe) == -1){
		perror(NULL);
		exit(1);
	}
	char buf[] = "abcdef";
	int pipeSize = 0;
	int n;
	close(fdPipe[0]);
	while( (n = write(fdPipe[1], buf, 6) ) > 0 ){

		pipeSize += n;
	}
	printf("%d\n",pipeSize);
	return 0;
}
