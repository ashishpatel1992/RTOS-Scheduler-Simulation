/**
 * @file periodic_scheduler.c
 * @author Ashish Patel (ashishpatel.1992@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include<stdio.h>
#include"task.h"
#include"sched_queue.c"
/**
 * @brief Schedules the Periodic Tasks
 * 
 * @param task_list 
 * @param no_of_tasks 
 * @param hyperperiod 
 * @param frame_size 
 */
void periodic_scheduler(struct task *task_list,int no_of_tasks,int hyperperiod,int frame_size){
    long clock=0; // GLOBAL CLOCK
    
    long task_division[no_of_tasks];            // STORES LIST OF JOBS in EACH TASK (MUST RUN TILL HERE)
    // long frame_jitter[hyperperiod/frame_size];  // JITTER IN EACH FRAME
    long frame_count=0;                         // Current Frame number
    long task_division_counter[no_of_tasks];    // Tells current job progress in each task
    memset(task_division_counter,0,sizeof(task_division_counter)); // SET all task to job 0
    
    // Allocates number of jobs in each Task
    for (size_t i = 0; i < no_of_tasks; i++)
    {
        task_division[i] = hyperperiod/task_list[i].period;
        // printf("\nDiv %ld",task_division[i]);
    }
    
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

        // Check for Ti whether it can fit in frame or not
        for (size_t task_id = 0; task_id < no_of_tasks; task_id++)
        {
             
            long arrival_time = task_list[task_id].period * task_division_counter[task_id];
            double execution_time = task_list[task_id].execution_time;
            long abs_deadline_time = task_list[task_id].relative_deadline * (task_division_counter[task_id]+1);
            double prev_frame_min_time = (clock - frame_size)+0.01;
            double prev_frame_max_time = (clock);

            //printf("\nFor %ld,%ld -- %ld >= %.2lf && %ld <= %.2lf",task_id,task_division_counter[task_id],arrival_time ,prev_frame_min_time, arrival_time, prev_frame_max_time);
            
            // check if job fits in frame, if it fits add it into the Ready Queue
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

        
        // Take jobs from ready queue and schedule them when slack is available
        for(int i=0;i<q_size;i++){
            struct QNode curr_node = deQueue(local_q); 
            double curr_task_exec_time = task_list[curr_node.task_id].execution_time;
            // printf("\n IF COND %.2lf <= %.2lf ",curr_task_exec_time, available_frame_time);
            
            // if condition is true schedule the job and remove it from Ready Queue
            // Otherwise, keep it aside so that we can try to schedule it in next frame
            if( curr_task_exec_time <= available_frame_time){
                task_division_counter[curr_node.task_id]++;
                available_frame_time = available_frame_time - curr_task_exec_time;
                printf("\nJob Executed J%ld,%ld",curr_node.task_id+1,task_division_counter[curr_node.task_id]);
                
            }else{ 
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
    printf("\n\n================= Scheduling till Hyperperiod %ld) =================\n",clock);
    int check_schedulable=1; 
    for(int i=0;i<no_of_tasks;i++){
        // check if all the jobs are scheduled till the end of hyperperiod
        // Otherwise, set check_schedulable = 0; i.e. All jobs cannot fit in a hyperperiod
        if(task_division_counter[i] != task_division[i]){
            check_schedulable=0;
        }
    }
    if(check_schedulable != 0){
        printf("\nFor given Taskset all Jobs are Periodic Jobs are Schedulable");
    }else{

        printf("\nGiven Taskset is NOT Schedulable");
    }
    
}
