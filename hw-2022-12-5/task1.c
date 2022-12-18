#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void * f0(void *){
	printf("0\n");
}

void * f1(void *){
        printf("1\n");
}

void * f2(void *){
        printf("2\n");
}

void * f3(void *){
        printf("3\n");
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
