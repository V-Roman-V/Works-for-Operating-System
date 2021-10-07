#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>
#include <string.h>

void printRusage(const struct rusage *ru)
{
	printf("ru_utime: %ld %ld\n",ru->ru_utime.tv_sec, ru->ru_utime.tv_usec);
	printf("ru_stime: %ld %ld\n",ru->ru_stime.tv_sec, ru->ru_stime.tv_usec);
	printf("ru_stime: %ld \n",ru->ru_ixrss);
	printf("ru_maxrss: %ld \n",ru->ru_maxrss);
	printf("ru_ixrss: %ld \n",ru->ru_ixrss);
	printf("ru_idrss: %ld \n",ru->ru_idrss);
	printf("ru_isrss: %ld \n",ru->ru_isrss);
	printf("ru_minflt: %ld \n",ru->ru_minflt);
	printf("ru_majflt: %ld \n",ru->ru_majflt);
	printf("ru_nswap: %ld \n",ru->ru_nswap);
	printf("ru_inblock: %ld \n",ru->ru_inblock);
	printf("ru_oublock: %ld \n",ru->ru_oublock);
	printf("ru_msgsnd: %ld \n",ru->ru_msgsnd);
	printf("ru_msgrcv: %ld \n",ru->ru_msgrcv);
	printf("ru_nsignals: %ld \n",ru->ru_nsignals);
	printf("ru_nvcsw: %ld \n",ru->ru_nvcsw);
	printf("ru_nivcsw: %ld \n",ru->ru_nivcsw);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

int main(void) {
	int size = 10*1024*1024;
  struct rusage data;
	for(int i = 0; i<10; i++){
		char* mem = (char*)malloc(size); // 1 Gi
		memset(mem, 0,size);
		getrusage(RUSAGE_SELF, &data);
		printRusage(&data);
		sleep(1);
	}
  return 0;
}
