/**
 * Implementation of thread pool.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "threadpool.h"
#include "queue.h"

#define QUEUE_SIZE 10
#define NUMBER_OF_THREADS 3

int poolState = 1;
pthread_mutex_t mutex;
// the work queue
queue taskQueue;

task workTodo;

// the worker bee
pthread_t bee;

// insert a task into the queue
// returns 0 if successful or 1 otherwise, 
int enQueue(task t) {
    if (taskQueue.size == QUEUE_SIZE) {
        return 1;
    }

    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = &t;
    newNode->next = NULL;
    if (taskQueue.head == NULL) {
        taskQueue.head = newNode;
        taskQueue.tail = newNode;
    } else {
        taskQueue.tail->next = newNode;
        taskQueue.tail = newNode;
    }
    taskQueue.size++;
    return 0;
}

// remove a task from the queue
task deQueue() {
    task *newTask;
    if (taskQueue.size == 0) {
        newTask = malloc(sizeof(task));
        newTask->function = NULL;
        return (task) *newTask;
    }

    newTask = taskQueue.head->task;
    taskQueue.head = taskQueue.head->next;
    taskQueue.size--;
    return (task) *newTask;
}

// the worker thread in the thread pool
void *worker(void *param) {
    // execute the task
    while (taskQueue.size > 0 || poolState) {
        pthread_mutex_lock(&mutex);
        workTodo = deQueue();
        pthread_mutex_unlock(&mutex);
        if (workTodo.function == NULL) {
            continue;
        }
        execute(workTodo.function, workTodo.data);
    }

    pthread_exit(0);
}

/**
 * Executes the task provided to the thread pool
 */
void execute(void (*someFunction)(void *), void *p) {
    (*someFunction)(p);
}

/**
 * Submits work to the pool.
 */
int pool_submit(void (*someFunction)(void *), void *param) {
    workTodo.function = someFunction;
    workTodo.data = param;

    int lockState = pthread_mutex_lock(&mutex);
    int state = enQueue(workTodo);
    pthread_mutex_unlock(&mutex);

    if (!lockState || state) {
        return 1;
    }
    return 0;
}

// initialize the thread pool
void pool_init(void) {
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&bee, NULL, worker, NULL);
}

// shutdown the thread pool
void pool_shutdown(void) {
    poolState = 0;

    pthread_join(bee, NULL);
    pthread_mutex_destroy(&mutex);
}