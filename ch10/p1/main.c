#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "virtual_memory_manager.h"

#define LOGICAL_ADDRESS_LENGTH 10

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("invalid args");
        return 1;
    }

    virtual_memory_manager_init("BACKING_STORE.bin");

    char *logical_address_file = argv[1];
    FILE *in;
    in = fopen(logical_address_file, "r");

    char *output_file = "test.txt";
    FILE *out;
    out = fopen(output_file, "w");

    char logical_address[LOGICAL_ADDRESS_LENGTH];
    while (fgets(logical_address, LOGICAL_ADDRESS_LENGTH, in) != NULL) {
        int value = get_value(atoi(logical_address), out);
    }
    fclose(in);
    fclose(out);

    printf("page fault rate:");
    printf("%f", get_page_fault_rate());
    printf("\n");

    printf("TLB hit rate:");
    printf("%f", get_TLB_hit_rate());
    printf("\n");

    printf("page replacement rate:");
    printf("%f", get_page_replacement_rate());
    printf("\n");

    return 0;
}