#include <stdio.h>
#include "task2_read.cpp"

void read_and_invert(){
	printf("Enter the string: ");
	char str[82];
	int n = 0;
	char ch;
	while ((ch = getchar()) != EOF && n < 82 && (ch = getchar()) != "\n"){
		str[n] = ch;
		++n;
	}
	for (int i = n; i >= 0; ++i)
      		putchar(str[i]);
   	putchar('\n');
}

int main(){
	read_and_invert();
	return 0;
}
