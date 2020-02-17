//
// Created by dxy on 2020/2/11.
//

#include <stdlib.h>

#define MIN_PID 300
#define MAX_PID 5000

int allocate_map(char *bitmap) {

    int size = MAX_PID - MIN_PID;
    int byteSize = size >> 3;
    if (size % 8 != 0) {
        byteSize++;
    }
    for (int i = 0; i < byteSize; ++i) {
        bitmap[i] = 0;
    }
    return 1;
}

int allocate_pid(char *bitmap) {
    int i = 0;
    int size = MAX_PID - MIN_PID;
    int byteSize = size >> 3;
    if (size % 8 != 0) {
        byteSize++;
    }

    while (i != byteSize && bitmap[i] == 0xff) {
        i++;
    }
    if (i == byteSize) {
        return -1;
    }

    i = i << 3;
    for (int j = 0; j < 8; ++j) {
        int pid = i + j;
        if (!(bitmap[pid >> 3] & (1 << (pid & 0x7)))) {
            bitmap[pid >> 3] |= (1 << (pid & 0x7));
            return pid;
        }
    }

    return -1;
}

void release_pid(char *bitmap, int pid) {
    bitmap[pid >> 3] &= ~(1 << (pid & 0x7));
}

int main() {
    char *bitmap = malloc((MAX_PID - MIN_PID) / 8);
    allocate_map(bitmap);

    allocate_pid(bitmap);
    allocate_pid(bitmap);
    allocate_pid(bitmap);
    allocate_pid(bitmap);
    allocate_pid(bitmap);
    release_pid(bitmap, 1);
    release_pid(bitmap, 2);
    free(bitmap);
}