#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#define PAGE_TABLE_SIZE 256

int page_table[PAGE_TABLE_SIZE];

/* 
 * Initialize all the elements in page_table to -1,which means all pages don't have corresponding frames now.
 */
void page_table_init();

#endif