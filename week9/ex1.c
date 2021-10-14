#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NULL_ID -1

struct Page{
	// if number of pages is 100, number of hits:
	// 8 bit -> 93, 16 bit -> 94, 32 bit -> 98
	int id;
	uint16_t counter;
};

struct Main{
	uint32_t hit;
	uint32_t miss;
	uint32_t N;
	struct Page *pages;
};

void initFrames(struct Main *f){
	printf("Print the number of pages\n");
	scanf("%u",&f->N);
	f->hit=0;
	f->miss=0;
	f->pages = (struct Page*)malloc(f->N*sizeof(struct Page));
	for(uint32_t i = 0; i < f->N; i++){
		f->pages[i].counter=0;
		f->pages[i].id=-1;
	}
}

void getPage(struct Main *f, uint32_t id){
	
	char has = 0; 
	uint32_t index = 0; 
	for(uint32_t i = 0; i < f->N; i++)
		f->pages[i].counter >>= 1; // counter shift

	for(uint32_t i = 0; i < f->N; i++){
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

void printdata(struct Main *f, uint32_t id){
	for(uint32_t i = 0; i < f->N; i++)
		printf("i = %u id = %d %u\n",i,f->pages[i].id,f->pages[i].counter);
	printf("current page number %u\n\n", id);
}

void printHit(struct Main *f){
	printf("hit = %u miss = %u ratio = %.6f\n",f->hit,f->miss,(double)f->hit/f->miss);
}

int main(void) {
	struct Main frames;
	initFrames(&frames);
	FILE *file = fopen("input.txt", "r");
	if(file == NULL){
		printf("can't find file input.txt\n");
		return 1;
	}

	uint32_t id;
	while(fscanf(file,"%u",&id) != EOF){
		// printdata(&frames, id);
		getPage(&frames, id);
	}

	printHit(&frames);
	free(frames.pages);
  return 0;
}
