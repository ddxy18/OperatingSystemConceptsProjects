#include "page_table.h"

void page_table_init()
{
    for (int i = 0; i < PAGE_TABLE_SIZE; i++)
    {
        page_table[i] = -1;
    }
}