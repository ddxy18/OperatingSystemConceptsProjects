//
// Created by dxy on 2020/2/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

struct node **head;

void add(char *name, int priority, int burst) {
    if (head == NULL) {
        head = malloc(sizeof(struct node *));
    }

    Task *t = malloc(sizeof(Task));
    t->name = name;
    t->priority = priority;
    t->burst = burst;
    insert(head, t);
}

void schedule() {
    while (*head != NULL) {
        Task *t = (*head)->task;
        run(t, t->burst);
        delete(head, t);
    }
    free(head);
}