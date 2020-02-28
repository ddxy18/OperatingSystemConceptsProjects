#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "allocator.h"

#define COMMAND_MAX_LENGTH 20
#define ERROR_INFO_MAX_LENGTH 100

int execute_command(char *);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("invalid args");
        return 1;
    }

    int size = atoi(argv[1]);
    allocator_init(size);

    char command[COMMAND_MAX_LENGTH];
    while (1) {
        printf("allocator> ");
        fflush(stdout);

        // get command without '\n'
        fgets(command, COMMAND_MAX_LENGTH, stdin);
        command[strlen(command) - 1] = '\0';

        execute_command(command);
    }
    return 0;
}

/* 
 * return 0 means successful execution and 1 means failure
 */
int execute_command(char *command) {
    char *temp = strdup(command);
    char *keyword = strsep(&temp, " ");
    char error_info[ERROR_INFO_MAX_LENGTH];
    int result;

    if (strcmp(keyword, "C") == 0) {
        compact();
        return 0;
    } else if (strcmp(keyword, "STAT") == 0) {
        status_report();
        return 0;
    } else if (strcmp(keyword, "X") == 0) {
        result = exit_allocator(error_info);
        printf(error_info);
        printf("\n");
        return result;
    }

    char *args[3];
    int i = 0;
    while ((args[i] = strsep(&temp, " ")) != NULL) {
        i++;
    }

    if (i == 1) {
        result = release(atoi(args[0] + 1), error_info);
    } else if (i == 3) {
        result = request(atoi(args[0] + 1), atoi(args[1]), args[2][0], error_info);
    } else {
        printf("invalid command\n");
        return 1;
    }
    if (result == 1) {
        printf(error_info);
        printf("\n");
    }
    return result;
}