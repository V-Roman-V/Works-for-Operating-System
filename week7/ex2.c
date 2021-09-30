#include <stdio.h>
#include <stdlib.h>

int main(void) {

  printf("Enter the size of array\n");
	int N;
	scanf("%d",&N);

	int *arr = (int*)malloc(N * sizeof(int));
	for(int i = 0; i < N; i++)
		arr[i] = i;

	printf("Array:\n[");
	for(int i = 0; i < N; i++)
		printf("%d%s",arr[i], (i+1==N)?"":", ");
	printf("]\n");

	free(arr);
	
  return 0;
}
