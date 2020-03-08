#include <pthread.h>
#include <stdlib.h>
#include "student.h"
#include "teaching_assistant.h"

#define STUDENT_NUM 10

pthread_t *student_pid;
pthread_t ta_pid;
student *sutdent_array;
teaching_assistant ta;

void student_init()
{
    student_pid = malloc(sizeof(student) * STUDENT_NUM);
    sutdent_array = malloc(sizeof(student) * STUDENT_NUM);

    for (int i = 0; i < STUDENT_NUM; i++)
    {
        sutdent_array[i].state = PROGRAMMING;
        pthread_create(student_pid[i], NULL, student_task, &sutdent_array[i]);
    }
}

void ta_init()
{
    ta.state = SLEEPING;
    pthread_create(ta_pid, NULL, ta_task, &ta);
}