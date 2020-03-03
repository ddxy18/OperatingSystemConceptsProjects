#include "TLB.h"
#include "page_table.h"

void TLB_init() {
    for (int i = 0; i < TLB_size; i++) {
        TLB.TLB_array[i].page_number = -1;
    }
    TLB_hit_times = 0;
}

int TLB_detect(int page_number) {
    for (int i = 0; i < TLB_size; i++) {
        if (TLB.TLB_array[i].page_number == page_number) {
            TLB_hit_times++;
            return TLB.TLB_array[i].frame_number;
        }
    }
    return -1;
}

void update_TLB(int page_number) {
    int frame_number = page_table[page_number];
    int i = TLB.to_be_replaced;
    TLB.TLB_array[i].page_number = page_number;
    TLB.TLB_array[i].frame_number = frame_number;
    TLB.to_be_replaced = (TLB.to_be_replaced + 1) % TLB_size;
}