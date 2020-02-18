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

    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = newTask;

    struct node *insertPosition = *head;
    if (insertPosition == NULL) {
        *head = newNode;
        return;
    }
    while (insertPosition->next != NULL) {
        if (insertPosition->next->task->burst <= newTask->burst) {
            insertPosition = insertPosition->next;
        } else {
            break;
        }
    }

    if(insertPosition==*head&&insertPosition->task->burst>newTask->burst) {
        newNode->next=insertPosition;
        *head=newNode;
        return;
    }
    newNode->next = insertPosition->next;
    insertPosition->next = newNode;
}

void schedule() {
    while (*head != NULL) {
        Task *t = (*head)->task;
        run(t, t->burst);
        delete(head, t);
    }
    free(head);
}