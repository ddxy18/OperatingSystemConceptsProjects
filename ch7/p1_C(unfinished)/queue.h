//
// Created by dxy on 2020/2/21.
//

#ifndef P1_C_QUEUE_H

#define P1_C_QUEUE_H

#include "task.h"

struct node {
    task *task;
    struct node *next;
};

typedef struct {
    struct node *head;
    struct node *tail;
    int size;
} queue;

#endif //P1_C_QUEUE_H
