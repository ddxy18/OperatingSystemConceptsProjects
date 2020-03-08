//
// Created by asus on 2020/2/21.
//

#ifndef P1_C_TASK_H
#define P1_C_TASK_H

// this represents work that has to be
// completed by a thread in the pool
typedef struct {
    void (*function)(void *p);

    void *data;
} task;

#endif //P1_C_TASK_H
