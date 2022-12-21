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

void* sumCounter(void* arg){
	int* arr = (int*) arg;
	int thread_num = arr[0];
	for(int i = 1;i < subArrSize + 1; ++i){
		dif[thread_num]+=arr[i];
		if(abs(arr[i]) > maxDif[thread_num]){
			maxDif[thread_num] = abs(arr[i]);
			maxDay[thread_num] = thread_num * subArrSize + i - 1;
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
	int subArr[t][subArrSize+1];  //The first element of each subarray is his thread's number
	i = 0;
	for(int j = 0;j<t;++j){
		for(int k = 0;k < subArrSize+1;++k){
			if(k == 0){
				subArr[j][k] = j;
				continue;
			}
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
