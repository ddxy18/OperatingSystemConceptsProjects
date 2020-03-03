#ifndef LRU_REPLACEMENT_H
#define LRU_REPLACEMENT_H

struct r_node {
    int page_number;
    struct r_node *next;
};

typedef struct {
    struct r_node *head;
    struct r_node *rear;
} r_list;

r_list *LRU_list;

#endif