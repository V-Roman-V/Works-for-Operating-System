#include <stdio.h>

void swap(int* a, int* b){
	int t = *a;
	*a = *b;
	*b = t;
}

void bubble_sort(int arr[], int size) {
	for(int i = 0; i < size - 1; i++)
		for(int j = i+1; j < size; j++)
			if(arr[i] > arr[j])
				swap(&arr[i], &arr[j]);
}

void print_array(int arr[], int arr_size) {
	printf("[");
	for(int i = 0; i < arr_size; i++)
		printf("%d%c",arr[i],(i+1<arr_size)?',':']');
}

int main(){
	int array[25] = {73, 49, 17, 72, 34, 14, 31, 32, 52, 33, 7, 60, 1, 61, 13, 46, 34, 64, 81, 25, 33, 98, 89, 29, 31};
	printf("Array before sorting: ");
	print_array(array,25);
	bubble_sort(array,25);
	printf("\nArray after sorting: ");
	print_array(array,25);
	return 0;
}
