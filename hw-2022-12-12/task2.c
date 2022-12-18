#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <limits.h>

int s;
int subArrSize;
int* dif;
int* maxDay;
int* maxDif;
int thread_num;

void* sumCounter(void* arg){
	int* arr = (int*) arg;
	for(int i = 0;i<subArrSize; ++i){
		dif[thread_num]+=arr[i];
		if(abs(arr[i]) > maxDif[thread_num]){
			maxDif[thread_num] = abs(arr[i]);
			maxDay[thread_num] = thread_num * subArrSize + i;
		}
	}
}

int main(int argc, char* argv[]){
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
	dif = (int*)calloc(t,sizeof(int));
	maxDay = (int*)calloc(t,sizeof(int));
	maxDif = (int*)calloc(t,sizeof(int));
	for(i = 0;i<t;++i){
		thread_num = i;
		pthread_create(&trInd[i], NULL, sumCounter, (void*) &subArr[i][0]);
	}
	for(i = 0;i<t;++i){
		pthread_join(trInd[i],NULL);
	}
	int finMaxDay = 0;
	int finMaxDif = 0;
	for(i = 0;i<t;++i){
		if(maxDif[i] >= finMaxDif){
			finMaxDif = maxDif[i];
			finMaxDay = maxDay[i];
		}
		s += dif[i];
	}
	printf("%d %d\n", s, finMaxDay);

	free(dif);
	free(maxDay);
	free(maxDif);
	close(fd);
	return 0;
}
