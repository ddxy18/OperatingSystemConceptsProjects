#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "virtual_memory_manager.h"
#include "physical_memory.h"
#include "page_table.h"
#include "free_list.h"
#include "TLB.h"
#include "page_replacement.h"

int get_physical_address(int logical_address);

/* 
 * Get the corresponding frame numbers.
 * If a page fault occurs,a free frame is allocated to the page.
 */
int get_frame_number(int page_number);

/* 
 * Initialize all the elements in page_table to -1,which means all pages don't have corresponding frames now.
 */
void page_table_init();

void virtual_memory_manager_init(char *backing_store_file_name) {
    page_table_init();
    free_list_init();
    TLB_init();
    replacement_policy_init();
    backing_store = backing_store_file_name;
    address_reference_times = 0;
    page_fault_times = 0;
}

int get_value(int logical_address, FILE *log) {
    char arg[10];

    char output[100] = "Virtual address: ";
    sprintf(arg, "%d", logical_address);
    strcat(output, arg);

    strcat(output, " Physical address: ");
    int physical_address = get_physical_address(logical_address);
    sprintf(arg, "%d", physical_address);
    strcat(output, arg);

    strcat(output, " Value: ");
    int value = get_char(physical_address);
    sprintf(arg, "%d", value);
    strcat(output, arg);

    strcat(output, "\n");

    fputs(output, log);
    return value;
}

double get_page_fault_rate() {
    return (double) page_fault_times / address_reference_times;
}

double get_TLB_hit_rate() {
    return (double) TLB_hit_times / address_reference_times;
}

double get_page_replacement_rate() {
    return (double) page_replacement_times / address_reference_times;
}

int get_physical_address(int logical_address) {
    int page_number = logical_address >> 8;
    int frame_number = get_frame_number(page_number);

    return (frame_number - page_number) * PAGE_SIZE + logical_address;
}

int get_frame_number(int page_number) {
    update_replacement_policy(page_number, 'L');
    address_reference_times++;
    int frame_number = TLB_detect(page_number);

    if (frame_number != -1) {
        // TLB hit
        return frame_number;
    } else {
        // TLB miss and go for the page table
        if (page_table[page_number] != -1) {
            frame_number = page_table[page_number];
        } else {
            // page fault
            page_fault_times++;
            struct node *free_frame = remove_first_node();

            if (free_frame == NULL) {
                // page replacement
                frame_number = replace(page_number);
            } else {
                frame_number = free_frame->frame_number;
                page_table[page_number] = frame_number;
            }
            load_from_backing_store(page_number, backing_store);
            update_replacement_policy(page_number, 'F');
        }
        update_TLB(page_number);
        return frame_number;
    }
}

void page_table_init() {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = -1;
    }
}