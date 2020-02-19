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

    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = tid;
    __sync_fetch_and_add(&tid, 1);
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = newTask;

    struct node *insertPosition = *head;
    if (insertPosition == NULL) {
        *head = newNode;
        return;
    }
    while (insertPosition->next != NULL) {
        if (insertPosition->next->task->priority >= newTask->priority) {
            insertPosition = insertPosition->next;
        } else {
            break;
        }
    }

    if (insertPosition == *head && insertPosition->task->priority < newTask->priority) {
        newNode->next = insertPosition;
        *head = newNode;
        return;
    }
    newNode->next = insertPosition->next;
    insertPosition->next = newNode;
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
