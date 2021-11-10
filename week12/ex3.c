#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>




#define NUM_SHORTCUT 3
static const int code1[3] = {KEY_P, KEY_E, -1};
static const int code2[4] = {KEY_C, KEY_A, KEY_P, -1};
static const int code3[4] = {KEY_I, KEY_W, KEY_S, -1};
static const int *const shcut_code[NUM_SHORTCUT] = {code1, code2, code3};

static const char *const shcut_hints[NUM_SHORTCUT] = {
    "P,E",
    "C,A,P",
    "I,W,S"
};

static const char *const shcut_phrases[NUM_SHORTCUT] = {
    "I passed the Exam!",
    "Get some cappuccino!",
    "I want to sleep :("
};


int main(void)
{
    const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    
    int fd;
    if ((fd = open(dev, O_RDONLY)) == -1) {
        printf("Cannot open %s\n", dev);
        return 1;
    }
    
    int shcut_progress[NUM_SHORTCUT] = {0};
		
    printf("Shortcuts:\n");
		for(int i = 0; i < NUM_SHORTCUT; i++)
		    printf("  [%s]:\t'%s'\n",shcut_hints[i],shcut_phrases[i]);

    struct input_event ev;
    while (1) {
        read(fd, &ev, sizeof ev);
        if (ev.code != EV_SYN && 1 == ev.value){
            //printf("%s 0x%04x (%d)\n", "PRESSED", (int)ev.code, (int)ev.code);
        		for(int i = 0; i < NUM_SHORTCUT; i++){
        				int pr = shcut_progress[i];
        				shcut_progress[i] = (ev.code == shcut_code[i][pr]) ? (pr+1) : 0;
        				if(shcut_code[i][shcut_progress[i]] == -1){
        					printf("\n%s\n",shcut_phrases[i]);
        					shcut_progress[i] = 0;
        				}
        		}
        }
    }
    return 0;
}

