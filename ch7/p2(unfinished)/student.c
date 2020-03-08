#include <unistd.h>
#include "student.h"

void student_task(void *param)
{
    student *student = param;

    if (student->state == CONSULTING)
    {
        sleep(10);
    }
}

void consult()
{
    
}