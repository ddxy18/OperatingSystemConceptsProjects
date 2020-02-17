//
// Created by asus on 2020/2/13.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LINE 80 /* The maximum length command */
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    char *lastArgs[MAX_LINE / 2 + 1]; /* last command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    while (should_run) {
        printf("osh>");
        fflush(stdout);

        /* read command */
        char commandLine[MAX_LINE];
        fgets(commandLine, MAX_LINE, stdin);

        int i = 1, p = -1;
        args[0] = strtok(commandLine, " ");
        while (i < MAX_LINE / 2 + 1) {
            args[i] = strtok(NULL, " ");
            if (args[i] == NULL) {
                break;
            }
            if (p < 0) {
                if (strcmp(args[i], "|") == 0) {
                    p = i;
                }
            }
            i++;
        }
        if (i == MAX_LINE / 2 + 1) {
            fprintf(stderr, "command length overflow");
            continue;
        }
        /* remove '\n' */
        args[i - 1][strlen(args[i - 1]) - 1] = '\0';

        /* exit */
        if (strcmp(args[0], "exit") == 0) {
            return 0;
        }

        int pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork Failed");
            continue;
        } else if (pid == 0) {
            /* background task */
            if (strcmp(args[i - 1], "&") == 0) {
                args[i - 1] = NULL;
                i--;
            }

            /* repeat the last command */
            if (strcmp(args[0], "!!") == 0) {
                if (lastArgs[0] == NULL) {
                    fprintf(stderr, "No commands in history");
                    continue;
                }
                execvp(lastArgs[0], lastArgs);
                exit(0);
            }

            if (i > 2) {
                /* redirect input and output */
                if (strcmp(args[i - 2], ">") == 0) {
                    args[i - 2] = NULL;
                    int fd = open(args[i - 1], O_WRONLY | O_CREAT);
                    close(STDIN_FILENO);
                    dup2(fd, STDOUT_FILENO);
                } else if (strcmp(args[i - 2], "<") == 0) {
                    args[i - 2] = NULL;
                    int fd = open(args[i - 1], O_RDONLY | O_CREAT);
                    dup2(fd, STDIN_FILENO);
                }

                /* pipe */
                if (p > 0) {
                    args[p] = NULL;
                    int fd[2];
                    if (pipe(fd) == -1) {
                        fprintf(stderr, "Pipe failed");
                        return 1;
                    }
                    int pipePid = fork();
                    if (pipePid < 0) {
                        fprintf(stderr, "Fork Failed");
                    } else if (pipePid == 0) {
                        close(fd[WRITE_END]);
                        dup2(fd[READ_END], STDIN_FILENO);
                        execvp(args[p + 1], (const char *const *) (args + p + 1));
                    } else {
                        close(fd[READ_END]);
                        dup2(fd[WRITE_END], STDOUT_FILENO);
                        execvp(args[0], args);
                    }
                    exit(0);
                }
            }

            execvp(args[0], args);
            exit(0);
        } else {
            /* save the current command */
            int j = 0;
            while (args[j] != NULL) {
                int length=strlen(args[j])+1;
                lastArgs[j]=malloc(length);
                for (int k = 0; k < length; ++k) {
                    lastArgs[j][k] = args[j][k];
                }
                j++;
            }
            lastArgs[j]=NULL;

            if (strcmp(args[i - 1], "&") != 0) {
                int *status = NULL;
                wait(status);
            }
        }
    }
    return 0;
}