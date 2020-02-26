#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "banker.h"

#define SIZE 100

int main(int argc, char *argv[]) {
    if (argc != NUMBER_OF_RESOURCES + 1) {
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        available[i - 1] = atoi(argv[i]);
    }

    FILE *in;
    char *temp;
    char max[SIZE];
    char *file_name = "test.txt";

    in = fopen(file_name, "r");

    int i = 0;
    while (fgets(max, SIZE, in) != NULL) {
        temp = strdup(max);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            maximum[i][j] = atoi(strsep(&temp, ","));
        }

        free(temp);
        i++;
    }
    fclose(in);

    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            need[i][j] = maximum[i][j];
            allocation[i][j] = 0;
        }
    }

    while (1) {
        execute_command();
    }
}

void execute_command() {
    char command[SIZE];
    char *type;
    int args[NUMBER_OF_RESOURCES + 1];

    fgets(command, SIZE, stdin);
    char *temp;
    temp = strdup(command);
    type = strsep(&temp, " ");
    if (strcmp(type, "*\n") == 0) {
        print_property();
        return;
    } else if (strcmp(type, "q\n") == 0) {
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
            for (int j = 0; j < NUMBER_OF_RESOURCES; ++j) {
                if (need[i][j != 0) {
                    printf("some tasks need to be completed\n");
                }
                if (allocation[i][j] != 0) {
                    printf("some resources need to be released\n");
                }
            }
        }
        exit(0);
    }

    for (int i = 0; i < NUMBER_OF_RESOURCES + 1; i++) {
        args[i] = atoi(strsep(&temp, " "));
    }
    free(temp);

    if (strcmp(type, "RQ") == 0) {
        request_resources(args[0], args + 1);
    } else if (strcmp(type, "RL") == 0) {
        release_resources(args[0], args + 1);
    }
}