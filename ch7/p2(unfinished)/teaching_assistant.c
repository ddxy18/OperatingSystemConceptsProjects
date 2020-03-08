#include <unistd.h>
#include "teaching_assistant.h"

void ta_task(void *param)
{
    teaching_assistant *ta = param;
    if (ta->state == HELPING)
    {
        consult();
    }
}