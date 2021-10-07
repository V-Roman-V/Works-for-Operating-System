#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
	int size = 1024*1024*1024;
	for(int i = 0; i<10; i++){
		char* mem = (char*)malloc(size); // 1 Gi
		memset(mem, 0,size);
		sleep(1);
	}
  return 0;
}
