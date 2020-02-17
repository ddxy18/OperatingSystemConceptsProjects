//
// Created by dxy on 2020/2/11.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main() {
    const int SIZE = 4096;
    const char *name = "OS";
    int fd = 0, status = 0;
    char *ptr;

    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    ptr = (char *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (fork() == 0) {
        time_t start = time(NULL);
        sprintf(ptr, "%ld", start);
    } else {
        wait(&status);
        time_t end = time(NULL);
        printf((char *) (end - (time_t) ptr));
        shm_unlink(name);
    }
    return 0;
}
