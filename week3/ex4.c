#include <stdio.h>

void swap(int* a, int* b){
	int t = *a;
	*a = *b;
	*b = t;
}

void quicksorter(int arr[], int first, int last) {
	if(first >= last) return;
	int pivot = (first + last) / 2;
	int less = 0;
	for(int i = first; i <= last;i++)
		if( arr[i] < arr[pivot])
			less++;
	swap(&arr[first + less],&arr[pivot]);
	pivot = first + less;
	for(int i = 0, ind = pivot+1; i < less && ind <= last; ind++)
		if(arr[ind] < arr[pivot]){
			swap(&arr[ind], &arr[first + i]);
			ind--;
			i++;
		}
	quicksorter(arr,first,pivot-1);
	quicksorter(arr,pivot+1,last);
}

void quick_sort(int arr[], int size){
	quicksorter(arr,0,size-1);
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
	quick_sort(array,25);
	printf("\nArray after sorting: ");
	print_array(array,25);
	return 0;
}
