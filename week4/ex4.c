#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>


int main(){
	char str[256];
	while (1) {
		putchar('>');
    int status;
		fgets(str, 256, stdin);
		char* args[16];
		args[0] = strtok(str," \n");
		int cnt = 1;
		for(;cnt < 15; cnt++)
			if( (args[cnt] = strtok(NULL," \n")) == NULL)
				break;

		char in_bg = !strcmp(args[cnt-1], "&");

		if (!fork()){
			if (in_bg)
				args[cnt-1] = NULL;
			execvp(args[0], args);
			return 0;
		}

		sleep(1);
		if (!in_bg)
			waitpid(-1, &status, 0);
  }
  return 0;
}
