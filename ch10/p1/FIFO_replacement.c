#include <stdlib.h>
#include "page_table.h"
#include "FIFO_replacement.h"
#include "page_replacement.h"

/*
 * After calling the function,the user must free the returned node manually.
 */
struct r_node *get_replaced_frame();

struct r_node *r_pop();

void r_push(struct r_node *newnode);

void replacement_policy_init() {
    page_replacement_times = 0;
    FIFO_list = malloc(sizeof(r_list *));
    FIFO_list->head = NULL;
    FIFO_list->rear = NULL;
}

int replace(int page_number) {
    page_replacement_times++;
    struct r_node *tmp = get_replaced_frame();
    int frame_number = tmp->frame_number;
    page_table[tmp->page_number] = -1;
    free(tmp);
    page_table[page_number] = frame_number;
    return frame_number;
}

void update_replacement_policy(int page_number, char policy) {
    if (policy == 'F') {
        // push the loaded frame to the replacement FIFO_list
        int frame_number = page_table[page_number];
        struct r_node *newnode = malloc(sizeof(struct r_node *));
        newnode->frame_number = frame_number;
        newnode->page_number = page_number;
        newnode->next = NULL;
        r_push(newnode);
    }
}

struct r_node *get_replaced_frame() {
    struct r_node *tmp;
    while (page_table[(tmp = r_pop())->page_number] == -1);
    return tmp;
}

struct r_node *r_pop() {
    if (FIFO_list->head == NULL) {
        return NULL;
    }

    struct r_node *tmp = FIFO_list->head;
    FIFO_list->head = FIFO_list->head->next;
    tmp->next = NULL;
    return tmp;
}

void r_push(struct r_node *newnode) {
    if (FIFO_list->head == NULL) {
        FIFO_list->head = newnode;
        FIFO_list->rear = newnode;
    } else {
        FIFO_list->rear->next = newnode;
        FIFO_list->rear = newnode;
    }
}