#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <stdio.h>

#define FRAME_SIZE 256
#define FRAME_QUANTITY 128

char physical_memory[FRAME_QUANTITY][FRAME_SIZE];

int get_char(int physical_address);

/* 
 * Load a page from the backing store and save them to the given frame.
 */
void load_from_backing_store(int page_number, char *backing_store_file_name);

#endif