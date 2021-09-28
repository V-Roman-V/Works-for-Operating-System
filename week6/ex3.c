#include <stdio.h>

#define MAXJ 15
#define FIFO 0
#define SHORTEST 1
#define ROUND_ROBIN 2

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

struct job {
	char done;
	int num;
	int at, bt;
	int ct, tat, wt;
	int workedTime;
};

void swap(struct job *A, struct job *B){
	struct job t = *A;
	*A = *B;
	*B = t;
}

struct job jobs[MAXJ];
int job_count=0;

void parsefile(FILE* file){
	for (int i = 0; i < MAXJ; i++, job_count++){
		if(fscanf(file,"%d,%d",&jobs[i].at,&jobs[i].bt) == EOF)break;
		jobs[i].num = i;
		jobs[i].done = 0;
		jobs[i].workedTime = 0;
	}
}

void FIFOInterpreter(){
	//sorting by arrival time
	for(int i = 0; i < job_count; i++)
		for(int j = 1; j < job_count - i; j++)
			if(jobs[j-1].at > jobs[j].at)
				swap(&jobs[j-1], &jobs[j]);

	for (int i = 0, t = 0; i< job_count; i++){
		int start = max(t, jobs[i].at);
		jobs[i].wt   = start - jobs[i].at;
		jobs[i].ct   = start + jobs[i].bt;
		jobs[i].tat  = jobs[i].bt + jobs[i].wt;
		jobs[i].workedTime = jobs[i].bt;
		jobs[i].done = 1;
		t = jobs[i].ct;
	}

	//sorting back by number
	for(int i = 0; i < job_count; i++)
		for(int j = 1; j < job_count - i; j++)
			if(jobs[j-1].num > jobs[j].num)
				swap(&jobs[j-1], &jobs[j]);
}

int chooseProcessbyBurstTime(int t){
	int minSl, minBt, ind = -1;
	for(int i = 0; i < job_count; i++){
		if(jobs[i].done)continue;
		int sleep = max(t, jobs[i].at) - t;
		int bt    = jobs[i].bt;

		// 1) minSleep if equal: then 2) min burst time
		if(ind == -1 || (sleep < minSl) || ((sleep == minSl)&&(bt < minBt)) ){
			minSl = sleep;
			minBt = bt;
			ind   = i;
		}
	}
	return ind;
}

void ShortestFirstInterpreter(){
	for(int cnt = 0, t = 0; cnt < job_count; cnt++){
		int i = chooseProcessbyBurstTime(t);
		int start = max(t, jobs[i].at);
		jobs[i].wt = start - jobs[i].at;
		jobs[i].ct = start + jobs[i].bt;
		jobs[i].tat = jobs[i].bt + jobs[i].wt;
		jobs[i].workedTime = jobs[i].bt;
		jobs[i].done = 1;
		t = jobs[i].ct;
	}
}

int getNextRoundRobinProcess(int t, int prevI){
	int minSl, ind = -1;
	for(int sh = 1; sh <= job_count; sh++){
		int i = (prevI+sh)%job_count;
		if(jobs[i].done)continue;
		int sleep = max(t, jobs[i].at) - t;
		// 1) next with minSleep
		if(ind == -1 || (sleep < minSl)) {
			minSl = sleep;
			ind   = i;
		}
	}
	return ind;
}

void RoundRobinInterpreter(){
	int quant = 2;
	
	for(int i = -1, cnt = 0, t = 0; cnt < job_count;){
		i = getNextRoundRobinProcess(t, i);
		int start = max(t, jobs[i].at);
		jobs[i].wt = start - jobs[i].at - jobs[i].workedTime;
		jobs[i].ct = start + min(jobs[i].bt - jobs[i].workedTime, quant);
		jobs[i].tat = jobs[i].bt + jobs[i].wt;
		jobs[i].workedTime = min(jobs[i].workedTime + quant, jobs[i].bt);
		if(jobs[i].workedTime == jobs[i].bt){
			jobs[i].done = 1;
			cnt++;
		}
		printf("(%d)Time:%d - %d   i:%d wt:%d ct:%d tat:%d wdt:%d done:%d\n",t,start,jobs[i].ct, i,jobs[i].wt,jobs[i].ct,jobs[i].tat,jobs[i].workedTime, jobs[i].done);
		t = jobs[i].ct;
	}
}


void culculateData(int method){
	switch(method){
		case FIFO:
			FIFOInterpreter();break;
		case SHORTEST:
			ShortestFirstInterpreter();break;
		case ROUND_ROBIN:
			RoundRobinInterpreter();break;
	}
}

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

int main(void) {
	FILE *file = fopen("input.csv", "r");
	parsefile(file);
	culculateData(ROUND_ROBIN); // FIFO, SHORTEST, ROUND_ROBIN
	printData();
	
	fclose(file);
  return 0;
}
