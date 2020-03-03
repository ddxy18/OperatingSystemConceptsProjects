#include "physical_memory.h"
#include "page_table.h"

int get_char(int physical_address) {
    int frame_number = physical_address >> 8;
    unsigned int offset = ((unsigned int) physical_address) << 24 >> 24;
    return (int) physical_memory[frame_number][offset];
}

void load_from_backing_store(int page_number, char *backing_store_file_name) {
    int frame_number = page_table[page_number];
    FILE *backing_store = fopen(backing_store_file_name, "r");
    fseek(backing_store, page_number * FRAME_SIZE, SEEK_SET);
    fread(physical_memory[frame_number], sizeof(char), FRAME_SIZE, backing_store);
    fclose(backing_store);
}