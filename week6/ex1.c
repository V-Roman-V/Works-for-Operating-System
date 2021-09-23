#include <stdio.h>

#define MAXJ 10

struct job {
	int num;
	int at;
	int bt;
	int ct, tat, wt;
};

void swap(struct job *A, struct job *B){
	struct job t = *A;
	*A = *B;
	*B = t;
}

int max(int a, int b){
	return (a>b)?a:b;
}

struct job jobs[MAXJ];
int job_count=0;


void printData(){
	printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
	for (int i = 0; i< job_count; i++)
		printf("P%d\t%d\t%d\t%d\t%d\t%d\n", jobs[i].num, jobs[i].at, jobs[i].bt, jobs[i].ct, jobs[i].tat, jobs[i].wt);
	double att=0,wt=0;
	for (int i = 0; i< job_count; i++){
		att+=jobs[i].tat;
		wt +=jobs[i].wt;
	}
	att/=job_count;
	wt /=job_count;
	printf("Average Turnaround Time = %f\n", att);
	printf("Average WT = %f", wt);
}

void parsefile(FILE* file){
	for (int i = 0; i < MAXJ; i++, job_count++){
		if(fscanf(file,"%d,%d",&jobs[i].at,&jobs[i].bt) == EOF)break;
		jobs[i].num=i;
	}
}

void sortingByAT(){
	//sorting by arrival time
	for(int i = 0; i < job_count; i++)
		for(int j = 1; j < job_count - i; j++)
			if(jobs[i-1].at > jobs[i].at)
				swap(&jobs[i-1], &jobs[i]);
}

void sortingByNum(){
	//sorting by number
	for(int i = 0; i < job_count; i++)
		for(int j = 1; j < job_count - i; j++)
			if(jobs[i-1].num > jobs[i].num)
				swap(&jobs[i-1], &jobs[i]);
}

void culculateData(){
	sortingByAT();

	int cur_t = 0;
	for (int i = 0; i< job_count; i++){
		int start = max(cur_t, jobs[i].at);
		jobs[i].wt = start - jobs[i].at;
		jobs[i].ct = start + jobs[i].bt;
		jobs[i].tat = jobs[i].bt + jobs[i].wt;
		cur_t = jobs[i].ct;
	}

	sortingByNum();
}

int main(void) {
	FILE *file = fopen("input.csv", "r");
	parsefile(file);
	culculateData();
	printData();
	
	fclose(file);
  return 0;
}
