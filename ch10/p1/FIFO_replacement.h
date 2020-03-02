#ifndef FIFO_REPLACEMENT_H
#define FIFO_REPLACEMENT_H

struct replacement_node
{
    int frame_number;
    int page_number;
    struct replacement_node *next;
};

typedef struct
{
    struct replacement_node *head;
    struct replacement_node *rear;
} replacement_queue;

replacement_queue *queue;

int page_replacement_times;

void replacement_queue_init();

/*
 * After calling the function,the user must free the returned node manually.
 */
struct replacement_node *get_replaced_frame();

void r_push(struct replacement_node *newnode);

#endif