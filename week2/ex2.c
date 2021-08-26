#include <stdio.h>
#include <string.h>
#define BUF_SIZE 256

int main(void) {
	char str[BUF_SIZE];

	printf("Write string:\n");
	if(fgets(str, BUF_SIZE, stdin) == NULL){
		printf("Something went wrong when reading the string");
		return 1;
	}
	printf("Reverse string:\n");
	int i = strlen(str)-1;
	while(--i >= 0)
		printf("%c",str[i]);
	printf("\n");
	return 0;
}
