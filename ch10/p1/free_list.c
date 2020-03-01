#include <stdlib.h>
#include "free_list.h"
#include "physical_memory.h"

void free_list_init()
{
    free_list = malloc(sizeof(struct node *));
    free_list->frame_number = 0;
    free_list->next = NULL;

    struct node *tmp = free_list;
    for (int i = 1; i < FRAME_QUANTITY; i++)
    {
        struct node *newnode = malloc(sizeof(struct node *));
        newnode->frame_number = i;
        newnode->next = NULL;
        tmp->next = newnode;
        tmp = tmp->next;
    }
}

struct node *remove_first_node()
{
    if (free_list == NULL)
    {
        return NULL;
    }

    struct node *tmp = free_list;
    free_list = free_list->next;
    tmp->next = NULL;
    return tmp;
}

void add_free_frame(int frame_number)
{
    struct node *newnode = malloc(sizeof(struct node *));
    newnode->frame_number = frame_number;
    newnode->next = NULL;

    if (free_list == NULL)
    {
        free_list = newnode;
    }

    if (free_list->frame_number > frame_number)
    {
        newnode->next = free_list;
        free_list = newnode;
        return;
    }

    struct node *tmp = free_list;
    while (tmp->next != NULL && tmp->next->frame_number < frame_number)
    {
        tmp = tmp->next;
    }
    newnode->next = tmp->next;
    tmp->next = newnode;
}