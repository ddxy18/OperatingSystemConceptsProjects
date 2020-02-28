#include <stdlib.h>
#include "list.h"

int insert(list *list, struct node *newnode) {
    if (list->head == NULL) {
        list->head = newnode;
    } else {
        if (list->head->begin > newnode->begin) {
            newnode->next = list->head;
            list->head = newnode;
            return 0;
        }

        struct node *tmp = list->head;
        while (tmp->next != NULL && tmp->next->begin < newnode->begin) {
            tmp = tmp->next;
        }
        newnode->next = tmp->next;
        tmp->next = newnode;
    }
    return 0;
}

int delete(list *list, int begin) {
    if (list->head == NULL) {
        return 1;
    }

    // head node is the node to be removed
    if (list->head->begin == begin) {
        struct node *to_delete = list->head;
        list->head = list->head->next;
        free(to_delete);
        return 0;
    }

    struct node *tmp = list->head;
    while (tmp->next != NULL && tmp->next->begin < begin) {
        tmp = tmp->next;
    }

    // cannot find node satisfies node->begin=begin
    if (tmp->next == NULL || tmp->next->begin > begin) {
        return 1;
    }

    struct node *to_delete = tmp->next;
    tmp->next = tmp->next->next;
    free(to_delete);
    return 0;
}