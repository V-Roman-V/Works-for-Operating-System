#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 3

void* threadFunc(void* num){
	printf("Hello from thread %d\n", (int) num );
	pthread_exit(0);
}
int main() {
	pthread_t thread[N];
	for(int i = 0; i < N; i++){
		printf("Creating thread %d\n", i);
		pthread_create(&thread[i], NULL, threadFunc, (void*)i);
		pthread_join(thread[i], NULL);
		printf("Terminating of thread %d\n", i);
	}
	return 0;
}
/*
	Creating thread 0
	Hello from thread 0
	Terminating of thread 0
	Creating thread 1
	Hello from thread 1
	Terminating of thread 1
	Creating thread 2
	Hello from thread 2
	Terminating of thread 2
*/
