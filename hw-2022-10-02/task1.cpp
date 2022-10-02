#include <stdio.h>
#include <cstring>

int main(int argc,char* argv[]){
	int a;
	sscanf(argv[1],"%i",&a);
	char symbol[1];
	sscanf(argv[2],"%s",symbol);
	int b;
	sscanf(argv[3],"%i",&b);
	if(!strcmp(symbol, "+"))
		a+=b;
	if(!strcmp(symbol, "*"))
		a*=b;
	printf("%d\n",a);
	return 0;
}
