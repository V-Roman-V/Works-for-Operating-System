#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

static const char *const state[2] = {
    "RELEASED",
    "PRESSED "
};

int main(void)
{
    const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    
    int fd;
    if ((fd = open(dev, O_RDONLY)) == -1) {
        printf("Cannot open %s\n", dev);
        return 1;
    }
    
    struct input_event ev;
    while (1) {
        read(fd, &ev, sizeof ev);
        if (/*events.type != 4 && */ev.code != EV_SYN && 0 <= ev.value && ev.value <= 1)
            printf("%s 0x%04x (%d)\n", state[ev.value], (int)ev.code, (int)ev.code);

    }
    return 0;
}
