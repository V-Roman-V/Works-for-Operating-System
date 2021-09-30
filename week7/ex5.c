#include <stdio.h>
#include <stdlib.h>

int main () {
	char **s = (char**) malloc(sizeof(char*));
	char foo[] = "Hello World";
	*s = foo; // s[0] equal to *s
	printf ("s is %s\n", s[0]);
	s[0] = foo; 
	printf ("s[0] is %c\n", s[0][0]);
	return (0) ;
}
