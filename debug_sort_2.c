/*------------------------------------------------------------------------------
*  Copyright (c) 2020 The Simple Scheduler Project. All rights reserved.
*  Use of this source code is governed by a BSD-style license that can be found
*  in the LICENSE file.
*  Author: Ashish Patel
*  TAG: USE SAME JOB and coutner
*
*------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include"task.c"
#include"sched_util.c"

#include "util/libfort/fort.h"
#include "util/libfort/fort.c"
#include"int_queue.c"
extern long hyperperiod;
void periodic_scheduler(struct task *task_list,int no_of_tasks,int hyperperiod,int frame_size);



int main(int argc, char const *argv[])
{
    
    char ch;
    
    char file_name[50]="periodicSchedule_ajay.txt"; //EXAMPLE WITH VALID 3,4,5 FRAMES  HP 660
    // char file_name[50]="periodicSchedule2.txt"; //EXAMPLE WITH VALID 3,4,5 FRAMES  HP 660
    // char file_name[50]="periodicSchedule_jobslice.txt"; //EXAMPLE WITH VALID FRAMES ONLY 1
    // char file_name[50]="periodSchedule3_q7.txt"; 
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
        // printf("Task %d ",task_list[i].id);
        // printf("%.2lf ",task_list[i].phase);
        // printf("%.2lf ",task_list[i].period);
        // printf("%.2lf ",task_list[i].execution_time);
        // printf("%.2lf ",array_period[i]);
        // printf("%.2lf \n",task_list[i].relative_deadline);
    
    }
    fclose(fp);
    printf("INPUT DATA");
    // Generate Table
    ft_table_t *input_table = ft_create_table();
    ft_set_cell_prop(input_table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(input_table, "TaskID", "Phase", "Period", "Execution Time","Deadline");
    for(int i=0;i<no_of_tasks;i++){
        char task_id[100];
        char task_phase[100];
        char task_period[100];
        char task_execution[100];
        char task_relative_deadline[100];
        
        int_to_string(i+1,task_id ,10);
        int_to_string(task_list[i].phase,task_phase,10);
        int_to_string(task_list[i].period,task_period,10);
        float_to_string(task_list[i].execution_time,task_execution,2);
        int_to_string(task_list[i].relative_deadline,task_relative_deadline,10);

        ft_write_ln(input_table, task_id, task_phase, task_period, task_execution, task_relative_deadline);
    }
    printf("%s\n", ft_to_string(input_table));
    ft_destroy_table(input_table);
    printf("\nSolution:\n");
    hyperperiod = calc_hyperperiod(array_period,no_of_tasks);
    long frame_size = calc_frame_size(task_list,no_of_tasks);
    printf("HyperPeriod: %ld ",hyperperiod);
    printf("\tFrame Size: %ld",frame_size);
    periodic_scheduler(task_list,no_of_tasks,hyperperiod,frame_size);
    /**
     *  Schedule the periodic Jobs
     **/

    printf("\n");
    
    
    return 0;
}

void periodic_scheduler(struct task *task_list,int no_of_tasks,int hyperperiod,int frame_size){
    long clock=0; // GLOBAL CLOCK
    
    long task_division[no_of_tasks];            // STORES LIST OF JOBS in EACH TASK (MUST RUN TILL HERE)
    long frame_jitter[hyperperiod/frame_size];  // JITTER IN EACH FRAME
    long frame_count=0;                         // Current Frame number
    long task_division_counter[no_of_tasks];    // Tells current job progress in each task
    memset(task_division_counter,0,sizeof(task_division_counter)); // SET all task to job 0
    
    // Allocates number of jobs in each Task
    for (size_t i = 0; i < no_of_tasks; i++)
    {
        task_division[i] = hyperperiod/task_list[i].period;
        // printf("\nDiv %ld",task_division[i]);
    }
    
    
    // struct Queue* pending_q = createQueue(); 
    struct Queue *remaining_queue = createQueue(); // TASKS REMAINED AFTER FRAME EXECUTION 
    while( clock < hyperperiod){ //instead of clock try with frame_count
        frame_count++;
        printf("\n\n================= FRAME %ld (starts at %ld) =================",frame_count,clock);
        double available_frame_time = frame_size;

        // Local queue is used for adding new arrival jobs
        struct Queue* local_q = createQueue(); 
        for(int i=0;i<remaining_queue->size;i++){
            struct QNode tmp_node = deQueue(remaining_queue);
            enQueue(local_q,tmp_node.task_id,tmp_node.deadline);    
        }
        // printf("\nRemaining Q size: %ld",remaining_queue->size);
        // printf("\ndLocal q size: %ld",local_q->size);
        //FOR EACH TASK it will run
        for (size_t task_id = 0; task_id < no_of_tasks; task_id++)
        {
             
            long arrival_time = task_list[task_id].period * task_division_counter[task_id];
            double execution_time = task_list[task_id].execution_time;
            long abs_deadline_time = task_list[task_id].relative_deadline * (task_division_counter[task_id]+1);
            double prev_frame_min_time = (clock - frame_size)+0.01;
            double prev_frame_max_time = (clock);

            //printf("\nFor %ld,%ld -- %ld >= %.2lf && %ld <= %.2lf",task_id,task_division_counter[task_id],arrival_time ,prev_frame_min_time, arrival_time, prev_frame_max_time);
            if(arrival_time >=(prev_frame_min_time) && (arrival_time <= prev_frame_max_time)){ //problem if not able scheduled and moved to next frame
            //printf("\n (%ld,%ld,%.2lf,%ld)",task_id,arrival_time,execution_time,abs_deadline_time);
            debug_print("min: %.2lf max: %.2lf",prev_frame_min_time,prev_frame_max_time);
                enQueue(local_q,task_id,abs_deadline_time);
                //printf("\t SELECTED %ld",task_id);
            }
            // struct QNode curr_task = deQueue(local_q);
        }

        // printf("\nQueue Size before sorting : %ld",local_q->size); //CHECK WHY SIZE NOT WORKING
        
        queue_sort(local_q);
        // printf("\nQueue Size after sorting: %ld",local_q->size);
        int q_size = local_q->size;

        
        //PROCESSING THE READY QUEUE
        for(int i=0;i<q_size;i++){
            struct QNode curr_node = deQueue(local_q); //ALWAYS DEQUE SAMETASK which is WRONG
            double curr_task_exec_time = task_list[curr_node.task_id].execution_time;
            // printf("\n IF COND %.2lf <= %.2lf ",curr_task_exec_time, available_frame_time);
            if(  curr_task_exec_time<= available_frame_time){ //then schedule it and remove from queue
                task_division_counter[curr_node.task_id]++;
                available_frame_time = available_frame_time - curr_task_exec_time;
                printf("\nJob Executed J%ld,%ld",curr_node.task_id+1,task_division_counter[curr_node.task_id]);
                
            }else{ //otherwise putback into queue
                enQueue(remaining_queue,curr_node.task_id,curr_node.deadline);

                // insertAtQueueFront(local_q,curr_node.task_id,curr_node.deadline);
            }
        }
        printf("\nSlack: %.2lf",available_frame_time);
        // printf("\nAvailable Frame: %.2lf \t Remaining item in Queue %ld",available_frame_time,local_q->size);
        // printf("\nTask_Counter: ");
        // for(int i=0;i<no_of_tasks;i++){
        //     printf("%ld\t",task_division_counter[i]);
        // }
        
        clock=clock+frame_size;
        
    }
    printf("\n\n================= Scheduling ENDS at %ld) =================\n",clock);
    int check_schedulable=1;
    for(int i=0;i<no_of_tasks;i++){
        if(task_division_counter[i] != task_division[i]){
            check_schedulable=0;
        }
    }
    if(check_schedulable != 0){
        printf("\nGiven Taskset is Schedulable");
    }else{

        printf("\nGiven Taskset is NOT Schedulable");
    }
    
}


