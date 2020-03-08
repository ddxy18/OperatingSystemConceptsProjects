#include "student.h"

enum ta_state
{
    HELPING,
    SLEEPING,
};

typedef struct
{
    enum ta_state state;
    student *student;
} teaching_assistant;

void ta_task(void *param);