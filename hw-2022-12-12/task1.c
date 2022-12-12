#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]){
	int n;
	int m;
	int k;
	char* fileName = argv[4];
	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%d", &m);
	sscanf(argv[3], "%d", &k);
	int fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);

	srand(time(NULL));
	m = -m;
	int randomNum;
	write( fd, &n, sizeof(n));
	for(int i = 0; i < n; ++i){
		randomNum =  (rand() % (k - m + 1)) + m;
		write( fd, &randomNum, sizeof(randomNum));
	}

	close(fd);
 	return 0;
}
