/**
 * @brief A simple Task entity used in scheduling
 * 
 */
#ifndef _SCHED_task_C_
#define _SCHED_task_C_
struct task
{
    int id;                     // Task Identifier
    double phase;               // Phase of the Task
    double period;              // Period of the Task
    double execution_time;      // Execution time of the Task
    double relative_deadline;   // Relative Deadline of the task
};
#endif