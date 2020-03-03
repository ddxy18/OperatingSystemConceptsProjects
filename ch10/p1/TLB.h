#ifndef TLB_H
#define TLB_H

#include <time.h>

#define TLB_size 16

int TLB_hit_times;

typedef struct {
    int page_number;
    int frame_number;
} TLB_entry;

/* 
 * to_be_replaced points to the entry which will be moved if a TLB miss happens
 */
struct {
    TLB_entry TLB_array[TLB_size];
    int to_be_replaced;
} TLB;

/* 
 * This will set all the entry's page number to -1.
 */
void TLB_init();

/* 
 * If the given page number is existed in TLB,then the function will return the corresponding frame number.
 * Otherwise -1 will be returned.
 */
int TLB_detect(int page_number);

/* 
 * The TLB will choose the next entry in the TLB as the next one to be moved,say,set to_be_replaced+1.
 */
void update_TLB(int page_number);

#endif