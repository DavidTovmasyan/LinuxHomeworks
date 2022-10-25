#include <stdio.h>
#include "task2_read.hpp"

void read_and_invert(){
	printf("Enter the string: ");
	char str[82];
	int n = 0;
	int ch;
	while ((ch = getchar()) != EOF && n < 82 && ch != '\n'){
		str[n] = ch;
		++n;
	}
	for (int i = n-1; i >= 0; --i)
      		putchar(str[i]);
   	putchar('\n');
}

