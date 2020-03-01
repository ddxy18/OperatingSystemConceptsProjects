#ifndef FREE_LIST_H
#define FREE_LIST_H

struct node
{
    int frame_number;
    struct node *next;
};

struct node *free_list;

/* 
 * Add all the frames to the free list.
 */
void free_list_init();

/* 
 * Remove the first frame to satisfy a page fault.
 * After calling the function,the user must free the returned node manually.
 * If no free frame is now available,the function will return NULL.
 */
struct node *remove_first_node();

/* 
 * As the free list is sorted in an ascending order of frame_number,
 * so this function will add new free frame to an appropriate location.
 */
void add_free_frame(int frame_number);

#endif