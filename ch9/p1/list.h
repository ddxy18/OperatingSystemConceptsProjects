/* 
 * for all functions with return type of int,0 means successful execution and 1 the opposite
 */

#ifndef LIST_H
#define LIST_H

struct node {
    int pid;
    int begin;
    int size;
    struct node *next;
};

typedef struct {
    struct node *head;
} list;

int insert(list *, struct node *);

int delete(list *, int);

#endif