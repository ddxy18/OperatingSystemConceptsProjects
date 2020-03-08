enum student_state
{
    PROGRAMMING,
    WAITING,
    CONSULTING,
};

typedef struct
{
    enum student_state state;
} student;

void student_task(void *param);

void consult();
