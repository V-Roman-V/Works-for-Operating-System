#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	for (int i = 0; i < 5; i++)
		fork();
	sleep(5);
	return (0);
	//Each process, creates 2 child processes, therefore, with loop 3 times: 2 ^ 3 = 8 processes, with loop 5 times: 2 ^ 5 = 32 processes.
}
