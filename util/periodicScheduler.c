/*------------------------------------------------------------------------------
*  Copyright (c) 2020 The Simple Scheduler Project. All rights reserved.
*  Use of this source code is governed by a BSD-style license that can be found
*  in the LICENSE file.
*
*------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include"task.c"
#include"sched_util.c"
extern long hyperperiod;


int main(int argc, char const *argv[])
{
    
    char ch;
    // char file_name[50]="periodicSchedule2.txt";
    char file_name[50]="periodicSchedule_jobslice.txt";
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
    hyperperiod = calc_hyperperiod(array_period,no_of_tasks);
    printf("HyperPeriod: %ld \n",hyperperiod);
    printf("\nFrame Size: %ld",calc_frame_size(task_list,no_of_tasks));
    // printf("HyperPeriod: %.2lf \n",array_lcm_double(array_period,no_of_tasks));
    // for (size_t i = 0; i < no_of_tasks; i++)
    // {
    //   printf("\n val: %lf",array_exec[i]);
    // }
    
    printf("\n");
    fclose(fp);
    
    return 0;
}
