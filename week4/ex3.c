#include <stdlib.h>
#include <stdio.h>

int main() {
	char str[256];
	while(1) {
		fgets(str, 256, stdin);
		system(str);
	}
	return 0;
}
