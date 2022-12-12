#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <limits.h>

int s;
int subArrSize;
int maxDif = 0;
int maxDay = 0;
int curDay;

pthread_mutex_t mt;

void * sumCounter(void *  arg){
	pthread_mutex_lock(&mt);
	int* arr = (int*) arg;
	for(int i = 0;i < subArrSize;++i){
		s += arr[i];
		if(abs(arr[i]) > maxDif){
			maxDif = abs(arr[i]);
			maxDay = curDay;
		}
		++curDay;
	}
	pthread_mutex_unlock(&mt);
}

int main(int argc, char* argv[]){
	pthread_mutex_init(&mt, NULL);
	int t;
	sscanf(argv[1], "%d", &s);
	sscanf(argv[2], "%d", &t);
	char* fileName = argv[3];
	int fd  = open(fileName, O_RDONLY);
	int n;
	read(fd, &n, sizeof(n));
	int nums[n];
	int i = 0;
	while(read(fd, &nums[i], sizeof(nums[i]))){
		++i;
	}

	pthread_t trInd[t];
	if(n%t == 0){
		subArrSize = n/t;
	}else{
		subArrSize = n/t + 1;
	}
	int subArr[t][subArrSize];
	i = 0;
	for(int j = 0;j<t;++j){
		for(int k = 0;k<subArrSize;++k){
			if(i<n){
				subArr[j][k] = nums[i];
				++i;
			}else
				subArr[j][k] = 0;
		}
	}
	for(i = 0;i<t;++i){
		curDay = i*subArrSize;
		pthread_create(&trInd[i], NULL, sumCounter, (void*) &subArr[i][0]);
	}
	for(i = 0;i<t;++i){
		pthread_join(trInd[i], NULL);
	}
	printf("%d %d\n", s, maxDay);
	close(fd);
	pthread_mutex_destroy(&mt);
	return 0;
}
