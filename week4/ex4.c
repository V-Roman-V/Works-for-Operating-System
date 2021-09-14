#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(){
	char str[256];
	while (1) {
		fgets(str, 256, stdin);
		char* args[16];
		args[0] = strtok(str," \n");
		int cnt = 1;
		for(;cnt < 15; cnt++)
			if( (args[cnt] = strtok(NULL," \n")) == NULL)
				break;
		if (!strcmp(args[cnt-1], "&")){
		    if (!fork()){
		        args[cnt-1] = NULL;
		        execvp(args[0], args);
		        return 0;
		    }
		} else
		    execvp(args[0], args);
  }
  return 0;
}
