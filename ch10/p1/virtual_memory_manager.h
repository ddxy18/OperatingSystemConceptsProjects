#ifndef VIRTUAL_MEMORY_MANAGER_H
#define VIRTUAL_MEMORY_MANAGER_H

#include <stdio.h>

#define PAGE_SIZE 256

char *backing_store;

int address_reference_times;
int page_fault_times;

void virtual_memory_manager_init(char *backing_store_file_name);

/* 
 * Get value according to the logical address and write detailed log to the given file.
 */
int get_value(int logical_address, FILE *log);

double get_page_fault_rate();

double get_TLB_hit_rate();

#endif