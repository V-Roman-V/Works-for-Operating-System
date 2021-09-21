#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define mSleep(time) usleep((time) * 1000)
#define BUFFER_SIZE 2
#define maxDelay 100

int buff[BUFFER_SIZE];
int buffCount = 0;

char P_sleep = 0;
char C_sleep = 0;

int trans_count = 0;

void* producer(void* data) {
	while (1) {

		if (buffCount == BUFFER_SIZE){
			P_sleep = 1;
			while (P_sleep) mSleep(100);
		}

		buff[buffCount] = rand()%maxDelay;
		buffCount++;

		if (buffCount == 1)
			C_sleep = 0;
	}
}

void* consumer(void* data) {
	while (1) {
		if (buffCount == 0){
			usleep(20);// To increase the probability of breakage, because I have never encountered a race of signals in a 20 minute wait
			C_sleep = 1;
			while (C_sleep) mSleep(100);
		}

		int item = buff[buffCount-1];
		buff[buffCount-1] = 0;
		buffCount--;

		if (buffCount == BUFFER_SIZE - 1)
			P_sleep = 0;

		trans_count++;
		mSleep(item);
	}
}

void* informator(void* data){
	int old_count = trans_count;
	while(1){
		mSleep(30000);
		printf("Count of transactions = %d\n", trans_count);
		if( old_count == trans_count ){
			printf("There is a problem!!!");
			return 0;
		}
		old_count = trans_count;
		mSleep(30000);
	}
}

int main(int argc, char *argv[]){
	srand(time(NULL));
	pthread_t prod, cons, info;
	printf("Create producer and consumer\n");
	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);
	pthread_create(&info, NULL, informator, NULL);
	pthread_join(info, NULL);
	return 0;
}
/*
Create producer and consumer
Count of transactions = 45
Count of transactions = 140
Count of transactions = 234
Count of transactions = 332
Count of transactions = 425
Count of transactions = 474
Count of transactions = 474
There is a problem!!!
*/
