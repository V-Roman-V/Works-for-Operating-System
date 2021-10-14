#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NULL_ID -1

struct Page{
	int id;
	uint16_t counter;
};

struct Main{
	uint16_t hit;
	uint16_t miss;
	uint16_t N;
	struct Page *pages;
};

void initFrames(struct Main *f){
	printf("Print the number of pages\n");
	scanf("%hu",&f->N);
	f->hit=0;
	f->miss=0;
	f->pages = (struct Page*)malloc(f->N*sizeof(struct Page));
	for(uint16_t i = 0; i < f->N; i++){
		f->pages[i].counter=0;
		f->pages[i].id=-1;
	}
}

void getPage(struct Main *f, uint16_t id){
	
	char has = 0; 
	uint16_t index = 0; 
	for(uint16_t i = 0; i < f->N; i++)
		f->pages[i].counter >>= 1; // counter shift

	for(uint16_t i = 0; i < f->N; i++){
		if(f->pages[i].id == NULL_ID){ // check for null page
			index = i;
			break;
		}
		if(f->pages[i].id == id){ // checking for existing id
			has = 1;
			index = i;
			break;
		}
		if(f->pages[i].counter < f->pages[index].counter) // search page with minimum count
			index=i;
	}

	if(!has){ // replacement of the old page
		f->pages[index].id = id;
		f->pages[index].counter = 0;
		f->miss++;
	} else f->hit++;

	f->pages[index].counter |= 1 << (sizeof(f->pages[index].counter)*8 - 1);
}

void printdata(struct Main *f, uint16_t id){
	for(uint16_t i = 0; i < f->N; i++)
		printf("i = %hu id = %d %hu\n",i,f->pages[i].id,f->pages[i].counter);
	printf("current page number %hu\n\n", id);
}

void printHit(struct Main *f){
	printf("hit = %hu miss = %hu ratio = %.6f\n",f->hit,f->miss,(double)f->hit/f->miss);
}

int main(void) {
	struct Main frames;
	initFrames(&frames);
	FILE *file = fopen("input.txt", "r");
	if(file == NULL){
		printf("can't find file input.txt\n");
		return 1;
	}

	uint16_t id;
	while(fscanf(file,"%hu",&id) != EOF){
		printdata(&frames, id);
		getPage(&frames, id);
	}

	printHit(&frames);
	free(frames.pages);
  return 0;
}
