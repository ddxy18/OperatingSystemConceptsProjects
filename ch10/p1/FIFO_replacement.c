#include <stdlib.h>
#include "page_table.h"
#include "FIFO_replacement.h"

struct replacement_node *r_pop();

void replacement_queue_init()
{
    page_replacement_times = 0;
    queue = malloc(sizeof(struct replacement_queue *));
    queue->head = NULL;
    queue->rear = NULL;
}

struct replacement_node *get_replaced_frame()
{
    page_replacement_times++;
    struct replacement_node *tmp;
    while (page_table[(tmp = r_pop())->page_number] == -1)
        ;
    return tmp;
}

struct replacement_node *r_pop()
{
    if (queue->head == NULL)
    {
        return NULL;
    }

    struct replacement_node *tmp = queue->head;
    queue->head = queue->head->next;
    tmp->next = NULL;
    return tmp;
}

void r_push(struct replacement_node *newnode)
{
    if (queue->head == NULL)
    {
        queue->head = newnode;
        queue->rear = newnode;
    }

    queue->rear->next = newnode;
    queue->rear = newnode;
}