#include<stdio.h>
#include<math.h>
#include<float.h>
#include<limits.h>
#include"scheduler_datastructure.c"

#define debug_print(fmt, ...) \
            do { if (DEBUG)\
                    { \
                        fprintf(stderr, "\n\033[0;31m%s:%d:%s():\033[0;33m " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); \
                                fprintf(stderr,"\033[0m"); \
                            } \
                } while (0)
#define DEBUG 1


// Calculates GCD of two numbers
// Ref: https://www.geeksforgeeks.org/program-find-gcd-floating-point-numbers/
long hyperperiod;
double gcd_double(double a, double b);

double gcd_double(double a, double b) 
{ 
    if (a < b) 
            return gcd_double(b, a); 
    
        // base case 
        if (fabs(b) < 0.001) 
            return a; 
    
        else
            return (gcd_double(b, a - floor(a / b) * b)); 
} 
//Calculates GCD for multiple numbers
// int *arr - input numbers
double array_gcd_double(double arr[], int n) 
{ 
    double result = arr[0]; 
    for (int i = 1; i < n; i++) 
    { 
        result = gcd_double(arr[i], result); 
  
        if(result == 1) 
        { 
           return 1; 
        } 
    } 
    return result; 
} 

double array_lcm_double(double arr[], int n) 
{ 
    
    // Initialize result 
    double ans = arr[0]; 
  
    // ans contains LCM of arr[0], ..arr[i] 
    // after i'th iteration, 
    for (int i = 1; i < n; i++) 
        ans = (((arr[i] * ans)) / 
                (gcd_double(arr[i], ans))); 
  
    return ans; 
} 

double calc_hyperperiod(double arr[],int size){
    return array_lcm_double(arr,size);
}
int calc_max_exec_time(struct task *task_list,int size){
    int max_num=INT_MIN;
    for(size_t i=0;i<size;i++){
        if(task_list[i].execution_time > max_num){
            max_num = task_list[i].execution_time;
        }
    }
    return max_num;
}
int calc_max_period(struct task *task_list, int size){
    int max_period = INT_MIN;
    for (size_t i = 0; i < size; i++)
    {   
        if(task_list[i].period > max_period){
            max_period = task_list[i].period;
        }
    }
   
    return max_period;
}
// frame size should divide hyperperiod
long check_valid_max_number(struct task *task_list,int n,double frame_length){
    //TODO Hyperperiod factors
    short flag = 0; 
    for (size_t i = 0; i < n; i++)
    {
        double period = task_list[i].period;
        long period_by_frame = floor(period/frame_length) - (period/frame_length);
        // flag will ensure that there is atleast one framesize that devides Hyperperiod
        
        if(  period_by_frame == 0){
            flag = 1;
            return (long)frame_length;
               
        }
    }
    // OTHERWISE SPILT (NOT SURE WHEN TO SLPLIT)
    printf("\n Unable to find Frame length. Task may not be schedulable");
    exit(-1); //EXIT if we cannot find a frame length
        
    return -1;
}
long calc_final_frame_length(struct task *task_list,int n, DynamicArray *valid_frame_size_list){
    // POSSIBLE FRAME SIZE LIST CALCULATION from HYPERPERIOD
    int largest_frame = valid_frame_size_list->data[0];
    for (size_t i = 0; i < valid_frame_size_list->used; i++)
    {
        int f = valid_frame_size_list->data[i];
        // flag check whether at all the jobs are meeting constraint 2f-gcd(pi,f) <= Di
        int flag=0;
        for (size_t j = 0; j < n; j++)
        {
            int period =  task_list[j].period;
            int deadline = task_list[j].relative_deadline;
            int result = ((2* f) - gcd_double(period,f));
            if(result > deadline){
                flag = 1;
            }
        }
        if(flag == 0){
            //TODO: Check if sorting required in case valid_frame_size_list is not in ascending order
                debug_print("valid frame %d,",f);
                largest_frame = f;
            }
        
    }
    return largest_frame;
}
DynamicArray generate_valid_frames(int min_frame_length, struct task *task_list,int size){
    /**
     * @ModuleTest: REFER Fulltest2.c
     **/
    DynamicArray valid_frame_size_list;
    DynamicArray_init(&valid_frame_size_list,1);
    int max_period = calc_max_period(task_list,size);

    debug_print("\nMAXPERIOD: %d", max_period);

    for(int factor = min_frame_length; factor <= max_period; factor++){
        //Check if atleast factor of one of the tasks
        int flag =0;
        
        for (int j = 0; j < size; j++)
        {
            int task_period = task_list[j].period;
            if( task_period % factor == 0){
                flag =1;
            }
        }
        if(flag == 1){
            DynamicArray_insert(&valid_frame_size_list,factor);
        }
    }
    return valid_frame_size_list;

}
long calc_frame_size(struct task *task_list,int size){
    int min_frame_length;
    double frame_length;
    DynamicArray valid_frame_size_list;
    int optimal_frame_size;
    
    // Condition 1 f >= max(Ei)
    min_frame_length = calc_max_exec_time(task_list,size);
    

    // frame_length = check_valid_max_number(task_list,n,min_frame_length);

    // Condition 2 list of all possible frames
    valid_frame_size_list =  generate_valid_frames(min_frame_length,task_list,size);
    
    // debug_print("\nValid Frame Sizes:%c ",1);
    // for (size_t i = 0; i < valid_frame_size_list.used; i++)
    // {
    //     debug_print(" %d \t",valid_frame_size_list.array[i]);
    // }
    // debug_print("Hi %c",1);

    // Condition 3 calculating largest frame possible frame size using 2f-gcd
    frame_length = calc_final_frame_length(task_list,size,&valid_frame_size_list);

    return frame_length;
}
