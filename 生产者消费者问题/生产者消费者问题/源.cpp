#include<pthread.h>
#include<iostream>
#include<semaphore.h>
#include <Windows.h>
using namespace std;
#pragma comment(lib, "x86/pthreadVC2.lib")
sem_t num;
int sum = 100,counts=0;
void* producer(void * args){
	while (counts<50){
		cout << "new pro work start!" << endl;
		sem_wait(&num);
		if (sum < 100){
			sum++;
			cout << "new product!" << endl;
		}
		sem_post(&num);
	}
	return NULL;
}
void* consumer(void * args){
	while (counts<50){
		sem_wait(&num);
		if (sum==0)
			sem_post(&num);
		else
		{
			sum--;
			counts++;
			cout << "success!"<< endl;
			sem_post(&num);
		}
	}
	return NULL;
}
int main(){
	cout<<"pthread"<<endl;
	pthread_t id,id2;
	int i = 0;
	sem_init(&num, 0, 1);
	pthread_create(&id, NULL,producer, NULL);
	pthread_create(&id2, NULL, consumer, NULL);
	pthread_join(id, NULL);
	pthread_join(id2, NULL);
}