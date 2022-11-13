  GNU nano 4.8                                                      task2.cpp                                                                 
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

enum{BUF_SIZE = 256};

int main(int argc, char* argv[]){
<<<<<<< HEAD
	int fd = open(argv[1], O_RDONLY);
	char word1[10], word2[10], word3[10];
	int i;
	int n;
	char buf[BUF_SIZE];
	while((n = read(fd, buf, BUF_SIZE)) > 0){
		sscanf(buf, "%s %s %s", word1, word2, word3);
	}
	close(fd);

	if(fork() > 0){
		int inputFd = open(word2, O_RDONLY);
		dup2(inputFd, 0);
		close(inputFd);
		execlp(word1, word1, word3, NULL);
		exit(1);
	}
	return 0;
=======
        int fd = open(argv[1], O_RDONLY);
        char word1[10], word2[10], word3[10];
        int i;
        int n;
        char buf[BUF_SIZE];
        while((n = read(fd, buf, BUF_SIZE)) > 0){
                sscanf(buf, "%s %s %s", word1, word2, word3);
        }
        close(fd);

        if(fork() > 0){
                int inputFd = open(word2, O_RDONLY);
                dup2(inputFd, 0);
                close(inputFd);
                execlp(word1, word1, word3, NULL);
                exit(1);
        }
        return 0;
>>>>>>> 803cc6ed2ba39bb661cb6624981fde2a6c7f901e
}


