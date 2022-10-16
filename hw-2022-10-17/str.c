#include "str.h"
#include <stdio.h>
#include <ctype.h>

int string_length(const char* s){
	int i = 0;
	while(s[i] != '\0'){
		++i;
	}
	return i;
}

int num_digits(const char* s){
	int num = 0;
	for(unsigned int i = 0; i < string_length(s); ++i){
		if(isdigit(s[i]))
			++num;
	}
	return num;
}
