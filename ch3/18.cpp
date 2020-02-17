//
// Created by dxy on 2020/2/11.
//

#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        return 1;
    } else if (pid > 0) {
        sleep(20);
        exit(0);
    } else {
        exit(0);
    }
}
