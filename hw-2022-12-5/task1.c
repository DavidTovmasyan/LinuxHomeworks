#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int num;

void * f0(void *){
	num = 0;
	printf("%d\n", num);
}

void * f1(void *){
        num = 1;
        printf("%d\n", num);
}

void * f2(void *){
        num = 2;
        printf("%d\n", num);
}

void * f3(void *){
        num = 3;
        printf("%d\n", num);
}

int main(void){
	pthread_t t0,t1,t2,t3;
	pthread_create(&t0, NULL, f0, NULL);
	pthread_create(&t1, NULL, f1, NULL);
	pthread_create(&t2, NULL, f2, NULL);
	pthread_create(&t3, NULL, f3, NULL);
	pthread_join(t0, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	printf("Finished\n");
	return 0;
}
