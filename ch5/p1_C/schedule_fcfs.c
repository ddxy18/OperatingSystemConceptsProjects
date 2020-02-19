//
// Created by dxy on 2020/2/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

struct node **head;
int tid = 1;
int size = 0;
int averageTurnaroundTime = 0;
int averageResponseTime = 0;
int averageWaitingTime = 0;
int timer = 0;

void add(char *name, int priority, int burst) {
    size++;
    averageWaitingTime += burst;
    if (head == NULL) {
        head = malloc(sizeof(struct node *));
    }

    Task *t = malloc(sizeof(Task));
    t->name = name;
    t->priority = priority;
    t->burst = burst;
    t->tid = tid;
    __sync_fetch_and_add(&tid, 1);
    insert(head, t);
}

void schedule() {
    while (*head != NULL) {
        Task *t = (*head)->task;
        averageResponseTime += timer;
        run(t, t->burst);
        timer += t->burst;
        averageTurnaroundTime += timer;
        delete(head, t);
    }
    averageWaitingTime = (averageTurnaroundTime - averageWaitingTime) / size;
    averageTurnaroundTime /= size;
    averageResponseTime /= size;
    free(head);
}