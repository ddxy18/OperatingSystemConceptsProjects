//
// Created by dxy on 2020/2/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "cpu.h"
#include "list.h"

struct node **head;
int tid = 1;
int size = 0;
int averageTurnaroundTime = 0;
int averageResponseTime = 0;
int averageWaitingTime = 0;
int timer = 0;

void newInsert(struct node **head, Task *task) {
    int priority = task->priority;
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = task;
    newNode->next = *(head + priority - 1);
    *(head + priority - 1) = newNode;
}

void newInsertToEnd(struct node **head, Task *newTask) {
    int priority = newTask->priority;

    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = newTask;
    newNode->next = NULL;
    if (*(head + priority - 1) == NULL) {
        *(head + priority - 1) = newNode;
        return;
    }
    struct node *tmp = *(head + priority - 1);
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = newNode;
}

void newDelete(struct node **head, Task *task) {
    struct node *temp;
    struct node *prev;
    int priority = task->priority;

    temp = *(head + priority - 1);
    // special case - beginning of list
    if (strcmp(task->name, temp->task->name) == 0) {
        *(head + priority - 1) = (*(head + priority - 1))->next;
    } else {
        // interior or last element in the list
        prev = *(head + priority - 1);
        temp = temp->next;
        while (strcmp(task->name, temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

void add(char *name, int priority, int burst) {
    size++;
    averageWaitingTime += burst;
    if (head == NULL) {
        head = malloc(sizeof(struct node *) * MAX_PRIORITY);
    }

    Task *t = malloc(sizeof(Task));
    t->name = name;
    t->priority = priority;
    t->burst = burst;
    t->tid = tid;
    __sync_fetch_and_add(&tid, 1);
    newInsert(head, t);
}

void schedule() {
    for (int i = MAX_PRIORITY - 1; i >= 0; --i) {
        int j = 0;
        int iSize = 0;
        struct node *tmp = head[i];
        while (tmp != NULL) {
            tmp = tmp->next;
            iSize++;
        }
        while (head[i] != NULL) {
            Task *t = head[i]->task;
            if (j < iSize) {
                averageResponseTime += timer;
                j++;
            }
            if (t->burst <= QUANTUM) {
                run(t, t->burst);
                timer += t->burst;
                averageTurnaroundTime += timer;
                newDelete(head, t);
            } else {
                run(t, QUANTUM);
                timer += QUANTUM;

                Task *newTask = malloc(sizeof(Task));
                newTask->name = t->name;
                newTask->priority = t->priority;
                newTask->burst = t->burst - QUANTUM;

                newDelete(head, t);
                newInsertToEnd(head, newTask);
            }
        }
    }
    averageWaitingTime = (averageTurnaroundTime - averageWaitingTime) / size;
    averageTurnaroundTime /= size;
    averageResponseTime /= size;
    free(head);
}
