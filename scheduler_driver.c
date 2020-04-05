/**
 * @file scheduler_driver.c
 * @author Ashish Patel (ashishpatel.1992@gmail.com)
 * @brief Driver file for Task scheduling
 * @version 1.0
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include"task.h"
#include"sched_util.c"
#include"periodic_scheduler.c"
#include "util/libfort/fort.h"
#include "util/libfort/fort.c"

extern long hyperperiod;

int main(int argc, char const *argv[])
{
    
    char ch;
    
    // char file_name[50]="periodicSchedule_ajay.txt"; //EXAMPLE WITH VALID 3,4,5 FRAMES  HP 660
    char file_name[50]="periodicSchedule3.txt";
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
    // Begin File Reading
    fscanf(fp,"%d",&no_of_tasks);
    
    // array containing all tasks
    struct task task_list[no_of_tasks];
    // array of all Tasks execution times, used for calculating Hyperperiod
    double array_period[no_of_tasks];
    // double array_execution[no_of_tasks];
    
    // read periodic schedule from file
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
    printf("\nINPUT DATA\n");
    // Generate Table for Input Data
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
    /**
     * @brief Schedules the Periodc Tasks
     * 
     */
    periodic_scheduler(task_list,no_of_tasks,hyperperiod,frame_size);
    printf("\n");
    
    
    return 0;
}



