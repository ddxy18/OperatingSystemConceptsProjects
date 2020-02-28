#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "allocator.h"

void print_stat(struct node *);

void combine_continuous_holes(struct node *);

int first_fit_request(struct node *, char *);

int best_fit_request(struct node *, char *);

int worst_fit_request(struct node *, char *);

void allocate_on_size(struct node *, struct node *);

void allocator_init(int size) {
    freeList.head = malloc(sizeof(struct node *));
    freeList.head->begin = 0;
    freeList.head->next = NULL;
    freeList.head->pid = -1;
    freeList.head->size = size;
}

/* 
 * All requests will be satisfied through appropriate selection of a hole.
 * if the selected hole is over twice the size of the requested space,
 * then the requested space is allocated and the remaining free space is seen as a new hole.
 */
int request(int pid, int size, char mode, char *error_info) {
    if (freeList.head == NULL) {
        strcpy(error_info, "all space is used up");
        return 1;
    }

    struct node *new_allocation = malloc(sizeof(struct node *));
    new_allocation->pid = pid;
    new_allocation->size = size;
    new_allocation->next = NULL;

    if (mode == 'F') {
        return first_fit_request(new_allocation, error_info);
    } else if (mode == 'B') {
        return best_fit_request(new_allocation, error_info);
    } else if (mode == 'W') {
        return worst_fit_request(new_allocation, error_info);
    } else {
        strcpy(error_info, "undefined allocation mode");
        return 1;
    }

    if (error_info == NULL) {
        return 0;
    } else {
        return 1;
    }
}

int release(int pid, char *error_info) {
    struct node *tmp = allocatedList.head;
    while (tmp != NULL && tmp->pid != pid) {
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        strcpy(error_info, "cannot find the process");
        return 1;
    } else {
        struct node *freenode = malloc(sizeof(struct node *));
        freenode->begin = tmp->begin;
        freenode->pid = -1;
        freenode->size = tmp->size;
        freenode->next = NULL;

        delete(&allocatedList, tmp->begin);
        insert(&freeList, freenode);
        combine_continuous_holes(freenode);
        return 0;
    }
}

void compact() {
    int address = 0;
    struct node *allocated_tmp = allocatedList.head;
    while (allocated_tmp != NULL) {
        allocated_tmp->begin = address;
        address += allocated_tmp->size;
        allocated_tmp = allocated_tmp->next;
    }

    int size = 0;
    struct node *free_tmp = freeList.head;
    while (free_tmp != NULL) {
        size += free_tmp->size;
        struct node *to_free = free_tmp;
        free_tmp = free_tmp->next;
        free(to_free);
    }

    if (size != 0) {
        freeList.head = malloc(sizeof(struct node *));
        freeList.head->begin = address;
        freeList.head->next = NULL;
        freeList.head->pid = -1;
        freeList.head->size = size;
    }
}

void status_report() {
    int address = 0;
    struct node *allocated_tmp = allocatedList.head;
    struct node *free_tmp = freeList.head;
    struct node *tmp;
    if (allocated_tmp == NULL) {
        tmp = free_tmp;
    } else if (free_tmp == NULL) {
        tmp = allocated_tmp;
    } else {
        tmp = allocated_tmp->begin == 0 ? allocated_tmp : free_tmp;
    }

    while (tmp != NULL) {
        print_stat(tmp);
        address += tmp->size;
        if (tmp == allocated_tmp) {
            allocated_tmp = allocated_tmp->next;
        } else {
            free_tmp = free_tmp->next;
        }
        if (allocated_tmp == NULL || free_tmp == NULL) {
            break;
        }
        tmp = (address == allocated_tmp->begin ? allocated_tmp : free_tmp);
    }

    while (allocated_tmp != NULL) {
        print_stat(allocated_tmp);
        allocated_tmp = allocated_tmp->next;
    }
    while (free_tmp != NULL) {
        print_stat(free_tmp);
        free_tmp = free_tmp->next;
    }
}

int exit_allocator(char *error_info) {
    if (allocatedList.head == NULL) {
        exit(0);
    } else {
        strcpy(error_info, "some processes wait to be freed");
        return 1;
    }
}

void print_stat(struct node *node) {
    printf("Addresses [");
    printf("%d", node->begin);
    printf(":");
    printf("%d", node->begin + node->size - 1);
    if (node->pid < 0) {
        printf("] Unused");
    } else {
        printf("] Process P");
        printf("%d", node->pid);
    }
    printf("\n");
}

/*
 * After every release the allocator will combine continuous holes,
 * so we only need to check the neighboring two node
 */
void combine_continuous_holes(struct node *node) {
    if (node->next != NULL) {
        // combine the node with its next node
        if (node->begin + node->size == node->next->begin) {
            struct node *to_free = node->next;
            node->next = to_free->next;
            node->size += to_free->size;
            free(to_free);
        }
    }

    // find the previous node
    struct node *tmp = freeList.head;
    while (tmp->next != NULL && tmp->next != node) {
        tmp = tmp->next;
    }
    // combine the node with its previous node
    if (tmp->begin + tmp->size == node->begin) {
        struct node *to_free = tmp->next;
        tmp->next = to_free->next;
        tmp->size += to_free->size;
        free(to_free);
    }
}

int first_fit_request(struct node *new_allocation, char *error_info) {
    struct node *tmp = freeList.head;
    while (tmp != NULL) {
        if (tmp->size >= new_allocation->size) {
            allocate_on_size(new_allocation, tmp);
            return 0;
        }
        tmp = tmp->next;
    }

    strcpy(error_info, "all holes cannot satisfy the requested size");
    return 1;
}

int best_fit_request(struct node *new_allocation, char *error_info) {
    struct node *tmp = freeList.head;
    struct node *fit = NULL;

    while (tmp != NULL) {
        if (tmp->size >= new_allocation->size) {
            if (fit != NULL) {
                if (tmp->size < fit->size) {
                    fit = tmp;
                }
            } else {
                fit = tmp;
            }
        }
        tmp = tmp->next;
    }

    if (fit != NULL) {
        allocate_on_size(new_allocation, fit);
        return 0;
    } else {
        strcpy(error_info, "all holes cannot satisfy the requested size");
        return 1;
    }
}

int worst_fit_request(struct node *new_allocation, char *error_info) {
    struct node *tmp = freeList.head;
    struct node *fit = NULL;

    while (tmp != NULL) {
        if (tmp->size >= new_allocation->size) {
            if (fit != NULL) {
                if (tmp->size > fit->size && tmp->size / 2 <= new_allocation->size) {
                    fit = tmp;
                }
            } else {
                fit = tmp;
            }
        }
        tmp = tmp->next;
    }

    if (fit != NULL) {
        allocate_on_size(new_allocation, fit);
        return 0;
    } else {
        strcpy(error_info, "all holes cannot satisfy the requested size");
        return 1;
    }
}

void allocate_on_size(struct node *new_allocation, struct node *fit) {
    new_allocation->begin = fit->begin;
    if (fit->size / 2 > new_allocation->size) {
        fit->begin += new_allocation->size;
        fit->size -= new_allocation->size;
    } else {
        new_allocation->size = fit->size;
        delete(&freeList, fit->begin);
    }
    insert(&allocatedList, new_allocation);
}