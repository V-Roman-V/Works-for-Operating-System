#include <stdio.h>
#include <stdlib.h>

void duplicate(char c, unsigned int count){
	for( int i = 0; i < count; i++)
		putchar(c);
}

void figure0(int n){
	for(int i = 0; i<n; i++){
		duplicate(' ', n - i - 1);
		duplicate('*', 1 + 2*i);
		duplicate(' ', n - i - 1);
		putchar('\n');
	}
}
void figure1(int n){
	for(int i = 0; i<n; i++){
		duplicate('*', 1 + i);
		duplicate(' ', n - i - 1);
		putchar('\n');
	}
}
void figure2(int n){
	for(int i = 0; i<n; i++){
		duplicate('*', 1 + n/2 - abs(n/2 - i));
		duplicate(' ', 1 + abs(n/2 - i));
		putchar('\n');
	}
}
void figure3(int n){
	for(int i = 0; i<n; i++){
		duplicate('*', n);
		putchar('\n');
	}
}

int readInt(){
	char num[32];
	if(fgets(num, 32, stdin) == NULL){
		printf("Something went wrong when reading the number");
		return 0;
	}
	return atoi(num);
}


int main(void) {
	void(*fig[4])(int);
	fig[0] = &figure0;
	fig[1] = &figure1;
	fig[2] = &figure2;
	fig[3] = &figure3;

	printf("Enter the number of the figure [1;4]:\n");
	int num = readInt();
	if (num < 1 || 4 < num){
		printf("Incorrect number:\n");
		return 0;
	}
	printf("Enter the height of the figure:\n");
	int h = readInt();
	fig[num-1](h);
	return 0;
}
