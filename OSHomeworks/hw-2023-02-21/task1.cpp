#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <cstddef>

pthread_mutex_t mutex;
std::string dest;

void copy_string(std::string& s1, const std::string& s2){
	s1 += s2;
}

void* func(void* arg){
	pthread_mutex_lock(&mutex);
	std::string* temp = (std::string*) arg;
	copy_string(dest, *temp);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, char* argv[]){
	pthread_mutex_init(&mutex, NULL);
	std::string src = argv[1];
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
	for(std::size_t i = 0;i < 4; ++i){
		pthread_create(&tr[i], NULL, func, (void*)  &strs[i]);
	}
	for(std::size_t i = 0;i < 4; ++i){
		pthread_join(tr[i], NULL);
	}
	std::cout << dest << "\n";
	pthread_mutex_destroy(&mutex);
	return 0;
}
