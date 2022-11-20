#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int pipeFd_1_2[2];
	int pipeFd_2_3[2];
	if(pipe(pipeFd_1_2) == -1){
		perror(NULL);
		exit(1);
	}
	if(pipe(pipeFd_2_3) == -1){
		perror(NULL);
		exit(1);
	}
	if(fork() == 0){
		close(pipeFd_1_2[0]);
		close(pipeFd_2_3[0]);
		close(pipeFd_2_3[1]);
		dup2(pipeFd_1_2[1], 1);
		close(pipeFd_1_2[1]);
		execlp(argv[1], argv[1], NULL);
		exit(1);
	}
	if(fork() == 0){
		close(pipeFd_1_2[1]);
		dup2(pipeFd_1_2[0], 0);
		dup2(pipeFd_2_3[1], 1);
		close(pipeFd_1_2[0]);
		close(pipeFd_2_3[0]);
		close(pipeFd_2_3[1]);
		execlp(argv[2], argv[2], NULL);
		exit(1);
	}
	char* args[argc-2];
	for(int i = 0; i < argc-3;++i){
		args[i] = argv[i+3];
	}
	args[argc-3] = NULL;
	if(fork() == 0){
		close(pipeFd_1_2[0]);
		close(pipeFd_1_2[1]);
		close(pipeFd_2_3[1]);
		dup2(pipeFd_2_3[0], 0);
		execvp(argv[3], args);
		exit(1);
	}
	wait(NULL);
	close(pipeFd_1_2[0]);
	close(pipeFd_1_2[1]);
	close(pipeFd_2_3[0]);
	close(pipeFd_2_3[1]);
	return 0;
}
