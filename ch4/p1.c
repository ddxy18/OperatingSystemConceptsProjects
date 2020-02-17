//
// Created by asus on 2020/2/16.
//

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define SIZE 9
enum TYPE {
    ROW, COLUMN, GRID
};

int **sudoku;
int validator = 1;

typedef struct {
    int n;
    enum TYPE type;
} task;

void setSudoku() {
    sudoku = malloc(sizeof(int *) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        sudoku[i] = malloc(sizeof(int) * SIZE);
    }
    sudoku[0][0] = 6;
    sudoku[0][1] = 2;
    sudoku[0][2] = 4;
    sudoku[0][3] = 5;
    sudoku[0][4] = 3;
    sudoku[0][5] = 9;
    sudoku[0][6] = 1;
    sudoku[0][7] = 8;
    sudoku[0][8] = 7;
    sudoku[1][0] = 5;
    sudoku[1][1] = 1;
    sudoku[1][2] = 9;
    sudoku[1][3] = 7;
    sudoku[1][4] = 2;
    sudoku[1][5] = 8;
    sudoku[1][6] = 6;
    sudoku[1][7] = 3;
    sudoku[1][8] = 4;
    sudoku[2][0] = 8;
    sudoku[2][1] = 3;
    sudoku[2][2] = 7;
    sudoku[2][3] = 6;
    sudoku[2][4] = 1;
    sudoku[2][5] = 4;
    sudoku[2][6] = 2;
    sudoku[2][7] = 9;
    sudoku[2][8] = 5;
    sudoku[3][0] = 1;
    sudoku[3][1] = 4;
    sudoku[3][2] = 3;
    sudoku[3][3] = 8;
    sudoku[3][4] = 6;
    sudoku[3][5] = 5;
    sudoku[3][6] = 7;
    sudoku[3][7] = 2;
    sudoku[3][8] = 9;
    sudoku[4][0] = 9;
    sudoku[4][1] = 5;
    sudoku[4][2] = 8;
    sudoku[4][3] = 2;
    sudoku[4][4] = 4;
    sudoku[4][5] = 7;
    sudoku[4][6] = 3;
    sudoku[4][7] = 6;
    sudoku[4][8] = 1;
    sudoku[5][0] = 7;
    sudoku[5][1] = 6;
    sudoku[5][2] = 2;
    sudoku[5][3] = 3;
    sudoku[5][4] = 9;
    sudoku[5][5] = 1;
    sudoku[5][6] = 4;
    sudoku[5][7] = 5;
    sudoku[5][8] = 8;
    sudoku[6][0] = 3;
    sudoku[6][1] = 7;
    sudoku[6][2] = 1;
    sudoku[6][3] = 9;
    sudoku[6][4] = 5;
    sudoku[6][5] = 6;
    sudoku[6][6] = 8;
    sudoku[6][7] = 4;
    sudoku[6][8] = 2;
    sudoku[7][0] = 4;
    sudoku[7][1] = 9;
    sudoku[7][2] = 6;
    sudoku[7][3] = 1;
    sudoku[7][4] = 8;
    sudoku[7][5] = 2;
    sudoku[7][6] = 5;
    sudoku[7][7] = 7;
    sudoku[7][8] = 3;
    sudoku[8][0] = 2;
    sudoku[8][1] = 8;
    sudoku[8][2] = 5;
    sudoku[8][3] = 4;
    sudoku[8][4] = 7;
    sudoku[8][5] = 3;
    sudoku[8][6] = 9;
    sudoku[8][7] = 1;
    sudoku[8][8] = 5;
}

void *executor(void *param) {
    task *t = (task *) param;
    int *checker = malloc(sizeof(int) * SIZE);
    memset(checker, 0, sizeof(int) * SIZE);

    if (t->type == ROW) {
        for (int i = 0; i < SIZE; ++i) {
            checker[sudoku[t->n][i] - 1]++;
        }
    } else if (t->type == COLUMN) {
        for (int i = 0; i < SIZE; ++i) {
            checker[sudoku[i][t->n] - 1]++;
        }
    } else {
        int row = t->n / 3 * 3;
        int column = t->n % 3 * 3;
        for (int i = row; i < row + 3; ++i) {
            checker[sudoku[i][column] - 1]++;
            checker[sudoku[i][column + 1] - 1]++;
            checker[sudoku[i][column + 2] - 1]++;
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        if (checker[i] != 1) {
            validator = 0;
            free(checker);
            return NULL;
        }
    }
    free(checker);
    return NULL;
}

void validate() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            task *t = malloc(sizeof(task));
            t->n = j;
            t->type = i;
            pthread_t tid;
            pthread_attr_t attr;

            pthread_attr_init(&attr);
            pthread_create(&tid, &attr, executor, t);
            pthread_join(tid, NULL);
        }
    }

    if (validator == 0) {
        printf("invalid sudoku!");
    } else {
        printf("valid sudoku");
    }
}