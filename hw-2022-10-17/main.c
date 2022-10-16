#include <stdio.h>
#include <ctype.h>
#include "str.c"

int main(int argc, char* argv[]){
	for(unsigned int i = 1;i<argc;++i){
		printf("%d %d\n",string_length(argv[i]),num_digits(argv[i]));
	}
	return 0;
}
