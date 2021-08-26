#include <stdio.h>
#include <stdlib.h>

void duplicate(char c, unsigned int count){
	for( int i = 0; i < count; i++)
		putchar(c);
}

int main(void) {
	printf("Enter the height of the triangle:\n");
	char num[32];
	if(fgets(num, 32, stdin) == NULL){
		printf("Something went wrong when reading the number");
		return 1;
	}
	int n = atoi(num);
	for(int i = 0; i<n; i++){
		duplicate(' ', n - i - 1);
		duplicate('*', 1 + 2*i);
		duplicate(' ', n - i - 1);
		putchar('\n');
	}
	return 0;
}
