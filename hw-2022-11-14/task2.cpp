#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int fdPipe[2];
	if(pipe(fdPipe) == -1){
		perror(NULL);
		exit(1);
	}
	char filler = 'a';
	int pipeSize = 0;
	int n;
	while( (n = write(fdPipe[1], &filler, sizeof(filler)) ) > 0 ){
		pipeSize += n;
		printf("%d\n", pipeSize);
	}
	close(fdPipe[0]);
	close(fdPipe[1]);
	return 0;
}
