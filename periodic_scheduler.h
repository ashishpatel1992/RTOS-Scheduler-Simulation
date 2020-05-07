#ifndef PERIODIC_SCHEDULER_H_
#define PERIODIC_SCHEDULER_H_
#include"task.h"
#include"sched_queue.h"
void periodic_scheduler(struct task *task_list,int no_of_tasks,int hyperperiod,int frame_size);
#endif