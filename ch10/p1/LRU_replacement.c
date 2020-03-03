#include <stdlib.h>
#include "LRU_replacement.h"
#include "page_replacement.h"
#include "page_table.h"

struct r_node *r_pop();

/* 
 * This function will find the page number in the LRU_list and remove it.
 * 
 * @return the removed node 
 * If the page number isn't in the LRU_list,it will return NULL.
 */
struct r_node *r_remove(int page_number);

void r_push(struct r_node *newnode);

void replacement_policy_init() {
    page_replacement_times = 0;
    LRU_list = malloc(sizeof(r_list *));
    LRU_list->head = NULL;
    LRU_list->rear = NULL;
}

int replace(int page_number) {
    page_replacement_times++;
    struct r_node *tmp = r_pop();
    int frame_number = page_table[tmp->page_number];
    page_table[tmp->page_number] = -1;
    // remove the replaced page from LRU_list
    struct r_node *n = r_remove(tmp->page_number);
    if (n != NULL) {
        free(n);
    }
    free(tmp);
    page_table[page_number] = frame_number;
    return frame_number;
}

void update_replacement_policy(int page_number, char policy) {
    if (policy == 'L') {
        // delete page number from the list if it exists and push it into the rear
        struct r_node *tmp = r_remove(page_number);
        if (tmp != NULL) {
            r_push(tmp);
        } else {
            struct r_node *newnode = malloc(sizeof(struct r_node *));
            newnode->page_number = page_number;
            newnode->next = NULL;
            r_push(newnode);
        }
    }
}

struct r_node *r_pop() {
    if (LRU_list->head == NULL) {
        return NULL;
    }

    struct r_node *tmp = LRU_list->head;
    LRU_list->head = LRU_list->head->next;
    tmp->next = NULL;
    return tmp;
}

struct r_node *r_remove(int page_number) {
    if (LRU_list->head == NULL) {
        return NULL;
    }

    if (LRU_list->head->page_number == page_number) {
        struct r_node *tmp = LRU_list->head;
        LRU_list->head = LRU_list->head->next;
        tmp->next = NULL;
        return tmp;
    }

    struct r_node *tmp = LRU_list->head;
    while (tmp->next != NULL) {
        if (tmp->next->page_number == page_number) {
            struct r_node *n = tmp->next;
            tmp->next = n->next;
            n->next = NULL;
            if (LRU_list->rear->page_number == page_number) {
                LRU_list->rear = tmp;
            }
            return n;
        }
        tmp = tmp->next;
    }

    return NULL;
}

void r_push(struct r_node *newnode) {
    if (LRU_list->head == NULL) {
        LRU_list->head = newnode;
        LRU_list->rear = newnode;
    } else {
        LRU_list->rear->next = newnode;
        LRU_list->rear = newnode;
    }
}