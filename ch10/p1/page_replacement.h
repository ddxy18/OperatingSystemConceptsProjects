#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H

int page_replacement_times;

void replacement_policy_init();

/* 
 * This function will choose a page to be replaced
 * and update page table for the removed page and newly loaded page.
 * Different page replacement algorithms all have to implement this function.
 * 
 * @return the chosen frame number
 */
int replace(int page_number);

/* 
 * If the virtual memory manager takes a page replacement policy,
 * the virtual memory manager must call this function to notice replacement handler to update information after every page fault happens.
 * 
 * @param policy 'F' refers FIFO replacement policy
 *               'L' refers LRU replacement policy
 */
void update_replacement_policy(int page_number, char policy);

#endif