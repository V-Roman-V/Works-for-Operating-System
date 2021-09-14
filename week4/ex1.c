#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t n = fork();

    if (n) 
      printf("Hello from parent [PID - %d]\n", getpid());
		else
			printf("Hello from child [PID - %d]\n", getpid());

    return 0;
}
/*
Hello from parent [PID - 31537]
Hello from child [PID - 31538]
Hello from parent [PID - 31539]
Hello from child [PID - 31540]
Hello from parent [PID - 31541]
Hello from child [PID - 31542]
Hello from parent [PID - 31543]
Hello from child [PID - 31544]
Hello from parent [PID - 31545]
Hello from child [PID - 31546]
Hello from parent [PID - 31547]
Hello from child [PID - 31548]
Hello from parent [PID - 31549]
Hello from child [PID - 31550]
Hello from parent [PID - 31551]
Hello from child [PID - 31552]
Hello from parent [PID - 31553]
Hello from child [PID - 31554]
Hello from parent [PID - 31555]
Hello from child [PID - 31556]
*/
