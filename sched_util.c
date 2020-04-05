/**
 * @file sched_util.c
 * @author Ashish Patel (ashishpatel.1992@gmail.com)
 * @brief Set of ulitity helper functions
 * @version 1.0
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include<stdio.h>
#include<math.h>
#include<float.h>
#include<limits.h>
#include"sched_dynamicarray.c"
#include"util/stringencoders/modp_numtoa.c"
/**
 * @brief debug_print used for printing debuggin information on screen
 * 
 */
#define debug_print(fmt, ...) \
            do { if (DEBUG)\
                    { \
                        fprintf(stderr, "\n\033[0;31m%s:%d:%s():\033[0;33m " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); \
                                fprintf(stderr,"\033[0m"); \
                            } \
                } while (0)
/**
 * @brief DEBUG 0 turns off the debugging mode
 *        DEBUG 1 turns on the debugging mode
 * 
 */
#define DEBUG 0


// Calculates GCD of two numbers
// Ref: https://www.geeksforgeeks.org/program-find-gcd-floating-point-numbers/
/**
 * @brief Stores Hyperperiod value globally
 * 
 */
long hyperperiod;

/**
 * @brief Calculates GCD for Floating point double value upto 3 decimals
 * 
 * @param a 
 * @param b 
 * @return double 
 */
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
/**
 * @brief Calculates GCD for array of Floating point double values
 * 
 * @param arr 
 * @param n 
 * @return double 
 */
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
/**
 * @brief Calculates LCM for array of Floating point double values
 * 
 * @param arr array of periods of all the tasks in taskset
 * @param n size of taskset
 * @return double 
 */
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
/**
 * @brief Returns the value calculated by array_lcm_double
 * 
 * @param arr array of periods of all the tasks in taskset
 * @param size size of taskset
 * @return double 
 */
double calc_hyperperiod(double arr[],int size){
    return array_lcm_double(arr,size);
}

/**
 * @brief Returns maximum execution time of task from task_list
 * 
 * @param task_list 
 * @param size size of taskset
 * @return int 
 */
int calc_max_exec_time(struct task *task_list,int size){
    int max_num=INT_MIN;
    for(size_t i=0;i<size;i++){
        if(task_list[i].execution_time > max_num){
            max_num = task_list[i].execution_time;
        }
    }
    return max_num;
}
/**
 * @brief Returns maximum Period of task from task_list
 * 
 * @param task_list 
 * @param size size of taskset
 * @return int 
 */
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
/**
 * @brief Validates and returns the final frame that satisfies following condition
 *              for every Ti, 2f – gcd(f, pi) ≤ Di 
 * 
 * @param task_list 
 * @param n size of taskset
 * @param valid_frame_size_list 
 * @return long 
 */
long calc_final_frame_length(struct task *task_list,int n, DynamicArray *valid_frame_size_list){
    // POSSIBLE FRAME SIZE LIST CALCULATION from HYPERPERIOD
    int largest_frame = valid_frame_size_list->data[0];
    // printf("\n Hi: %d",largest_frame);
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
            
            // TO SATISFY 2f - gcd(pi,f) <= Di
            // if any of the Task result > Di we might not be able to find right frame
            // Task may or maynot be schedulable
            if(result > deadline){
                //printf("\n %d > %d for task %lu",result,deadline,i);
                // if(i == 2) continue;
                flag = 1;
            }
        }
        if(flag == 0){
                debug_print("valid frame %d,",f);
                largest_frame = f;
            }
        
    }
    return largest_frame;
}
/**
 * @brief Generates list of all valid frames for the given taskset
 * 
 * @param min_frame_length minimum frame size that you can choose
 * @param task_list 
 * @param size size of taskset
 * @return DynamicArray 
 */
DynamicArray generate_valid_frames(int min_frame_length, struct task *task_list,int size){
    
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
/**
 * @brief Returns the best frame size out of all the possible frames generated by following conditions:-
 *          1) Minimum Context Switching
 *              f >= max(Ei)
 *          2) Minimization of Table Size (list o all possible valid frames)
 *              ⎣M/F⎦ = M/F 
 *          3) Satisfaction of Task Deadline
 *              for every Ti, 2f – gcd(f, pi) ≤ Di 
 * 
 * @param task_list 
 * @param size size of taskset
 * @return long 
 */
long calc_frame_size(struct task *task_list,int size){
    int min_frame_length;
    double frame_length;
    DynamicArray valid_frame_size_list;
    int optimal_frame_size;
    
    // Condition 1 f >= max(Ei)
    min_frame_length = calc_max_exec_time(task_list,size);
    

    // frame_length = check_valid_max_number(task_list,n,min_frame_length);

    // Condition 2 list of all possible valid frames
    valid_frame_size_list =  generate_valid_frames(min_frame_length,task_list,size);
    
    debug_print("\nValid Frame Sizes:%c ",1);
    for (size_t i = 0; i < valid_frame_size_list.used; i++)
    {
        debug_print(" %d \t",valid_frame_size_list.data[i]);
    }

    // Condition 3 calculating largest frame possible frame size using 2f-gcd
    frame_length = calc_final_frame_length(task_list,size,&valid_frame_size_list);

    return frame_length;
}

/**
 * @brief Converts an integer number into its equivalent string
 * 
 * @source https://github.com/Antscran/MSP430/blob/master/SM2432v1.1/ExtFunc/itoa.c
 * 
 * @param value input integer number
 * @param result output equivalent string
 * @param base base of the number
 * @return char* 
 */
char* int_to_string(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

/**
 * @brief Converts a floating point number into its equivalent string
 * 
 * @param value input float number
 * @param str ouput equivalent string
 * @param prec precision length
 * @return size_t returns NAN if given value is not a valid floating point number
 */
size_t float_to_string(double value, char* str, int prec)
{
    
   return modp_dtoa(value,str,prec);
}
