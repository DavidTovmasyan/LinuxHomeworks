#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <cstddef>

pthread_mutex_t mutex;
pthread_cond_t cond;
bool isAvailable = true;

void* printer_func(void* arg){
	std::string* text = (std::string*) arg;
	pthread_mutex_lock(&mutex);
	while(isAvailable == false){
		pthread_cond_wait(&cond, &mutex);
	}
	isAvailable = false;
	std::cout << *text << std::endl;
	isAvailable = true;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(){
	pthread_mutex_init(&mutex, NULL);
        pthread_t tr[2];
	std::string text1 = "Thread1";
	std::string text2 = "Thread2";
        pthread_create(&tr[0], NULL, printer_func, &text1);
	pthread_create(&tr[1], NULL, printer_func, &text2);
        pthread_join(tr[0], NULL);
	pthread_join(tr[1], NULL);
        pthread_mutex_destroy(&mutex);

	return 0;
}
