#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

enum {BUFF_SIZE = 64};

int main(int argc, char* argv[]){
	if(strcmp(argv[1], "save") == 0 ){
		printf("It works!!");
		int x;
		scanf("%d", &x);
		char result[32];
		int counter = 0;
		if (x == 0)
   			result[0] = '0';
		else{
   			int binaryNum[32];
			int i=0;
   			while (x > 0) {
	      			binaryNum[i++] = x % 2;
				x /= 2;
  	 		}
   			for (int j = i-1; j >=0; j--){
      				result[counter++] = binaryNum[j] + '0';
   			}
		}
		int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if(fd == -1){
			perror(argv[2]);
			return 1;
		}
		write(fd, result, counter);
		close(fd);
	}
	else
	return 0;
}
