#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#define PAGE_TABLE_SIZE 256

/* 
 * Page table can be modified by any components in the manager.
 */
int page_table[PAGE_TABLE_SIZE];

#endif