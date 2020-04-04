/**
 * Task Model with granularity of time unit 1
*/
//TODO Check granularity thing
#ifndef _SCHED_task_C_
#define _SCHED_task_C_
struct task
{
    int id;                 // Task Identifier
    double phase;
    double period;
    double execution_time;
    double relative_deadline;
};
#endif