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
#include"util/libfort/fort.c"

extern long hyperperiod;

int main(int argc, char const *argv[])
{
    char file_name[50];
    int no_of_tasks;
    FILE *read_fp, *write_fp;
    if (argc < 2) {
        printf("missing filename\n");
        exit(1);
    }
    
    strcpy(file_name, argv[1]);
    read_fp = fopen(file_name,"r");
    
    if(!read_fp){
        printf("\nERROR: Unable to open file '%s'. Please check whether file exist or not.\n",file_name);
        exit(EXIT_FAILURE);
    }
    
    // Begin File Reading
    printf("\nReading file %s",file_name);
    fscanf(read_fp,"%d",&no_of_tasks);
    
    // array containing all tasks
    struct task task_list[no_of_tasks];
    // array of all Tasks execution times, used for calculating Hyperperiod
    double array_period[no_of_tasks];
    // double array_execution[no_of_tasks];
    
    // read periodic schedule from file
    for(size_t i=0;i<no_of_tasks;i++){
        
        fscanf(read_fp,"%d",&task_list[i].id);
        fscanf(read_fp,"%lf",&task_list[i].phase);
        fscanf(read_fp,"%lf",&array_period[i]);

        task_list[i].period = array_period[i];
        fscanf(read_fp,"%lf",&task_list[i].execution_time);
        fscanf(read_fp,"%lf",&task_list[i].relative_deadline);
    
    }
    fclose(read_fp);

    
    write_fp = fopen("scheduler_output.txt", "w");
    if (write_fp == NULL) 
    { 
        printf("Could not open file"); 
        return 0; 
    } 
    fprintf(write_fp,"\nINPUT DATA\n");
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
    fprintf(write_fp,"%s\n", ft_to_string(input_table));
    ft_destroy_table(input_table);


    fprintf(write_fp,"\nSolution:\n");
    
    hyperperiod = calc_hyperperiod(array_period,no_of_tasks);
    long frame_size = calc_frame_size(task_list,no_of_tasks);

    fprintf(write_fp,"HyperPeriod: %ld ",hyperperiod);
    fprintf(write_fp,"\tFrame Size: %ld",frame_size);
    /**
     * @brief Schedules the Periodc Tasks
     * 
     */
    fclose(write_fp);
    periodic_scheduler(task_list,no_of_tasks,hyperperiod,frame_size);
    fprintf(write_fp,"\n");
    
    
    return 0;
}



