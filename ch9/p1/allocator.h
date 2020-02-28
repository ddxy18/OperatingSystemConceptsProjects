/* 
 * for all functions with return type of int,0 means successful execution and 1 the opposite
 */

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "list.h"

list allocatedList;
list freeList;

void allocator_init(int size);

int request(int pid, int size, char mode, char *error_info);

int release(int pid, char *error_info);

void compact();

void status_report();

int exit_allocator(char *error_info);

#endif