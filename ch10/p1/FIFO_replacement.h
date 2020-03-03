#ifndef FIFO_REPLACEMENT_H
#define FIFO_REPLACEMENT_H

struct r_node {
    int frame_number;
    int page_number;
    struct r_node *next;
};

typedef struct {
    struct r_node *head;
    struct r_node *rear;
} r_list;

r_list *FIFO_list;

#endif