#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

long long res[20];
unsigned int ind = 4;
pthread_mutex_t m;

long long divisors(long long n) {
	long long count = 0;
	for(long long i = 1; i <= n; ++i) {
		if(n % i == 0) {
			++count;
		}
	}
	return count;
}

enum{SIZE = 20};

void * func0(void* args){
	long long* arr = (long long*) args;
	res[0] = divisors(arr[0]);
	pthread_mutex_lock(&m);
	while(ind < SIZE){
		res[ind] = divisors(arr[ind]);
		++ind;
	}
	pthread_mutex_unlock(&m);
	return NULL;
}

void * func1(void* args){
        long long* arr = (long long*) args;
        res[1] = divisors(arr[1]);
        pthread_mutex_lock(&m);
        while(ind < SIZE){
                res[ind] = divisors(arr[ind]);
                ++ind;
        }
        pthread_mutex_unlock(&m);
      return NULL;
}

void * func2(void* args){
        long long* arr = (long long*) args;
        res[2] = divisors(arr[2]);
        pthread_mutex_lock(&m);
        while(ind < SIZE){
                res[ind] = divisors(arr[ind]);
                ++ind;
        }
        pthread_mutex_unlock(&m);
        return NULL;
}

void * func3(void* args){
        long long* arr = (long long*) args;
        res[3] = divisors(arr[3]);
        pthread_mutex_lock(&m);
        while(ind < SIZE){
                res[ind] = divisors(arr[ind]);
                ++ind;
        }
        pthread_mutex_unlock(&m);
        return NULL;
}


int main(int argc, char* argv[]) {
	pthread_mutex_init(&m, NULL);
	long long args[20];
	for(int i = 0; i < SIZE; ++i) {
		if(sscanf(argv[i+1], "%lli", &args[i]) != 1) {
			return 1;
		}
	}
	pthread_t t[4];
        pthread_create(&t[0], NULL, func0, args);
	pthread_create(&t[1], NULL, func1, args);
	pthread_create(&t[2], NULL, func2, args);
	pthread_create(&t[3], NULL, func3, args);

	for(int i = 0;i<4;++i){
		pthread_join(t[i], NULL);
	}
	for(long long i = 0; i < SIZE; ++i) {
		printf("%lld\t", res[i]);
	}
	pthread_mutex_destroy(&m);
	return 0;
}

