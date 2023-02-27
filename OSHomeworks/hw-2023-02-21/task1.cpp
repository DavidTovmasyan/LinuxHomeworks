#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <cstddef>

pthread_mutex_t mutex;
std::string dest;

struct passed_values{
	std::string sub_str;
	int start_ind;
	int end_ind;
};

//consider, that [start;end) includes in str and len(str2) = end-start
void copy_string(std::string& str1, std::string str2,  int start, int end){
	for(int i = start; i < end; ++i){
		str1[i] = str2[i-start];
	}
}

void* func(void* arg){
	pthread_mutex_lock(&mutex);
	passed_values* temp = (passed_values*) arg;
	copy_string( dest, (*temp).sub_str, (*temp).start_ind, (*temp).end_ind);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, char* argv[]){
	pthread_mutex_init(&mutex, NULL);
	std::string src = argv[1];
	dest.resize(src.size());
	std::string strs[4];
	for(std::size_t i = 0; i < src.size()/4;++i){
		strs[0].push_back(src[i]);
	}
	for(std::size_t i = src.size()/4; i < src.size()/2;++i){
                strs[1].push_back(src[i]);
        }
	for(std::size_t i = src.size()/2; i < (3*src.size())/4;++i){
		strs[2].push_back(src[i]);
	}
	for(std::size_t i = (3*src.size())/4; i < src.size();++i){
    	        strs[3].push_back(src[i]);
        }
	pthread_t tr[4];
	passed_values pv[4];
	for(std::size_t i = 0;i < 4; ++i){
		pv[i].sub_str = strs[i];
		pv[i].start_ind = ( i * src.size() ) / 4;
		pv[i].end_ind = ( (i+1) * src.size() ) / 4;
	}
	for(std::size_t i = 0;i < 4; ++i){
		pthread_create(&tr[i], NULL, func, (void*)  &pv[i]);
	}
	for(std::size_t i = 0;i < 4; ++i){
		pthread_join(tr[i], NULL);
	}
	std::cout << dest << "\n";
	pthread_mutex_destroy(&mutex);
	return 0;
}
