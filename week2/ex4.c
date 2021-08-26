#include <stdio.h>
#include <stdlib.h>

void swap(int* n1, int* n2){
	int t = *n1;
	*n1 = *n2;
	*n2 = t;
}

int main(void) {
	printf("Enter the two integer (in separate line):\n");
	char num1[32], num2[32];
	if(fgets(num1, 32, stdin) == NULL || fgets(num2, 32, stdin) == NULL){
		printf("Something went wrong when reading the number");
		return 1;
	}
	int n1 = atoi(num1), n2 = atoi(num2);
	printf("Number before swap: n1 = %d, n2 = %d \n",n1,n2);
	swap(&n1,&n2);
	printf("Number after  swap: n1 = %d, n2 = %d \n",n1,n2);
	return 0;
}
