#include <stdio.h>
#include <string.h>

# define FILE_NAME "input.txt"
# define RESOURCE_COUNT 3
# define PROCESS_COUNT  5

void readL(FILE* fptr, int (*a)[RESOURCE_COUNT]){
	for (int i = 0; i<RESOURCE_COUNT; i++)
		fscanf(fptr,"%i",&(*a)[i]);
}
void readM(FILE* fptr, int (*a)[PROCESS_COUNT][RESOURCE_COUNT]){
	for (int i = 0; i<PROCESS_COUNT; i++)
		for (int j = 0; j<RESOURCE_COUNT; j++)
			fscanf(fptr,"%i",&(*a)[i][j]);
}

char isMayFinish(int process, const int (* const R)[PROCESS_COUNT][RESOURCE_COUNT], const int (* const A)[RESOURCE_COUNT]){
	for (int j = 0; j < RESOURCE_COUNT; j++) 
		if ( (*R)[process][j] > (*A)[j])
			return 0;
	return 1;
}

int main(void) {
	FILE *fptr = fopen(FILE_NAME,"r");
	if(fptr == NULL){
		printf("File %s can not be open!\n",FILE_NAME);
		return 1;
	}

	int E[RESOURCE_COUNT], A[RESOURCE_COUNT];
	int C[PROCESS_COUNT][RESOURCE_COUNT], R[PROCESS_COUNT][RESOURCE_COUNT];
	readL(fptr, &E);
	readL(fptr, &A);
	readM(fptr, &C);
	readM(fptr, &R);

	char Finish[PROCESS_COUNT] = {0};
	int ans[PROCESS_COUNT], ind = 0;
	memset(ans, -1, PROCESS_COUNT * sizeof(int));

	for (int k = 0; k < PROCESS_COUNT && ind < PROCESS_COUNT; k++)
		for (int i = 0; i < PROCESS_COUNT; i++) 
			if (!Finish[i] && isMayFinish(i, &R, &A)) {
				ans[ind++] = i;
				for (int y = 0; y < RESOURCE_COUNT; y++)
					A[y] += C[i][y];
				Finish[i] = 1;
			}

	printf("\nStatus after execution\n");
	for (int i = 0; i < PROCESS_COUNT; i++)
		printf(" P%d: %s\n", i, (Finish[i])?"finished":"not finished");

	printf("\nFollowing is the safe Sequence\n");
	for (int i = 0; i < PROCESS_COUNT; i++)
		if(ans[i] != -1)
			printf(" P%d %s", ans[i], (i+1 != PROCESS_COUNT)?"->":"\n");
		else {
			printf(" X - deadlock\n");
			break;
		}

	char is_dl = 0;
	for (int i = 0; i < PROCESS_COUNT; i++)
		is_dl |= !Finish[i];
	
	if(is_dl){
		printf("\nDeadlock occurred with processes { ");
		for(int i = 0; i < PROCESS_COUNT; i++)
			if(!Finish[i])
				printf("%i ",i);
		printf("}\n");
	} else 
		printf("\nSituation is resolved without deadlock\n");

	fclose(fptr);
	return 0;
}
