#include <stdio.h>
#include <cstring>

int main(int argc,char* argv[]){
	int a;
	int b;
	int res;
       	sscanf(argv[1], "%i", &a);
	sscanf(argv[3], "%i", &b);
	if(!strcmp(argv[2], "*"))
                res = a * b;
	if(!strcmp(argv[2], "+"))
		res = a + b;
	printf("%i %i\n",a, b); 
	printf("%i\n", res);
	return 0;
}
