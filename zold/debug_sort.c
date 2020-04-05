/*------------------------------------------------------------------------------
*  Copyright (c) 2020 The Simple Scheduler Project. All rights reserved.
*  Use of this source code is governed by a BSD-style license that can be found
*  in the LICENSE file.
*   Useage of QUEUE
*------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include"task.c"
#include"sched_util.c"
#include<string.h>
// #include "util/libfort/fort.h"
// #include "util/libfort/fort.c"
#include"int_queue.c"
extern long hyperperiod;
void periodic_scheduler(struct task *task_list,int no_of_tasks,int hyperperiod,int frame_size);
void periodic_scheduler_using_queue(struct task *task_list,int no_of_tasks,int hyperperiod,int frame_size);



int main(int argc, char const *argv[])
{
    
    char ch;
    
    char file_name[50]="periodicSchedule3.txt"; //EXAMPLE WITH VALID 3,4,5 FRAMES  HP 660
    // char file_name[50]="periodicSchedule2.txt"; //EXAMPLE WITH VALID 3,4,5 FRAMES  HP 660
    // char file_name[50]="periodicSchedule_jobslice.txt"; //EXAMPLE WITH VALID FRAMES ONLY 1
    int no_of_tasks;
    FILE *fp;
    fp = fopen(file_name,"r");
    if(!fp){
        printf("\nERROR: Unable to open file '%s'. Please check whether file exist or not.\n",file_name);
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d",&no_of_tasks);
    // printf("%d",no_of_tasks);
    struct task task_list[no_of_tasks];
    // array of all Tasks execution times, used for calculating Hyperperiod
    double array_period[no_of_tasks];
    // double array_execution[no_of_tasks];
    
    // READ PERIODIC SCHEDULES FROM FILE
    for(size_t i=0;i<no_of_tasks;i++){
        
        fscanf(fp,"%d",&task_list[i].id);
        fscanf(fp,"%lf",&task_list[i].phase);
        fscanf(fp,"%lf",&array_period[i]);
        // fscanf(fp,"%lf",&task_list[i].period);
        task_list[i].period = array_period[i];

        // fscanf(fp,"%lf",&task_list[i].execution_time);
        
        fscanf(fp,"%lf",&task_list[i].execution_time);
    
        fscanf(fp,"%lf",&task_list[i].relative_deadline);
        printf("Task %d ",task_list[i].id);
        printf("%.2lf ",task_list[i].phase);
        printf("%.2lf ",task_list[i].period);
        printf("%.2lf ",task_list[i].execution_time);
        printf("%.2lf ",array_period[i]);
        printf("%.2lf \n",task_list[i].relative_deadline);
    
    }
        
    fclose(fp);
    hyperperiod = calc_hyperperiod(array_period,no_of_tasks);
    long frame_size = calc_frame_size(task_list,no_of_tasks);
    printf("HyperPeriod: %ld \n",hyperperiod);
    printf("\nFrame Size: %ld",frame_size);
    periodic_scheduler(task_list,no_of_tasks,hyperperiod,frame_size);
    /**
     *  Schedule the periodic Jobs
     **/

    printf("\n");
    
    
    return 0;
}
void periodic_scheduler(struct task *task_list,int no_of_tasks,int hyperperiod,int frame_size){
    long clock=0;
    
    // struct task task_division[no_of_tasks];
    long task_division[no_of_tasks];
    long jitter[hyperperiod/frame_size];
    long frame_count=1;

    for (size_t i = 0; i < no_of_tasks; i++)
    {
        task_division[i] = hyperperiod/task_list[i].period;
        printf("\nDiv %ld",task_division[i]);
    }
    
    long task_division_counter[no_of_tasks];
    memset(task_division_counter,0,sizeof(task_division_counter));
    // for (size_t i = 0; i < no_of_tasks; i++)
    // {
    //     printf("VAL: %ld",task_division_counter[i]);
    // }
    struct Queue* pending_q = createQueue();  
    while( clock < hyperperiod){ //instead of clock try with frame_count
        double available_frame_time = frame_size;

        // Local queue is used for adding new arrival jobs
        struct Queue* local_q = createQueue(); 

        for (size_t i = 0; i < no_of_tasks; i++)
        {
             
            long arrival_time = task_list[i].period * task_division_counter[i];
            double execution_time = task_list[i].execution_time;
            long abs_deadline_time = task_list[i].relative_deadline * (task_division_counter[i]+1);
            debug_print(" AT: %ld, E: %.2lf, abs_deadline: %ld ",arrival_time,execution_time,abs_deadline_time);
            double prev_frame_min_time = (clock - frame_size)+0.01;
            double prev_frame_max_time = (clock);
            debug_print("min: %.2lf max: %.2lf",prev_frame_min_time,prev_frame_max_time);
            if(arrival_time >=(prev_frame_min_time) && (arrival_time <= prev_frame_max_time)){ //problem if not able scheduled and moved to next frame

            }

        }
        printf("\n");
        clock++;
        
    }
    
    
}




void periodic_scheduler_using_queue(struct task *task_list,int no_of_tasks,int hyperperiod,int frame_size){
    long clock=0;
    long next_frame_time = frame_size;
    struct task task_division[no_of_tasks];
    // Queue task_division[no_of_tasks];
    // task_division()
    // Queue task
    struct Queue *q = createQueue(1);
    // q->array = &(task_list[0]);
    while(clock < hyperperiod){
        enqueue(q,task_list[0]);
        enqueue(q,task_list[1]);
        printf("\nQueue Size %d ",q->size);
        printf("\nclock %ld",clock);
        struct task  t= dequeue(q);
        printf("\nqueue item %d",t.id);
     clock++;   
    }
}