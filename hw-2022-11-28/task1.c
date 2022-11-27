#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int m;

void sigHandler(int sig){
	if(m > 0){
		--m;
		return;
	}
	if(m == 0){
		exit(sig);
	}
}

int main(int argc, char* argv[]){
	if(argc == 1){
		fprintf(stderr, "%s", "Not enough arguments\n");
		exit(1);
	}
	for(int i = 0;i < strlen(argv[1]); ++i){
		if(argv[1][i] == '-' && i==0)
			continue;
		if(!isdigit(argv[1][i])){
			fprintf(stderr, "%s", "The argument is not a number\n");
                	exit(2);
		}
	}


	sscanf(argv[1], "%d", &m);
	if(m < 0){
		fprintf(stderr, "%s", "The argument is negative\n");
                exit(3);
	}
	signal(SIGINT, sigHandler);
	while(1){
		sleep(2);
		printf("%d signals remaining\n", m);
	}
	return 0;
}
