/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
size_t float_to_string(double value,char *str,int prec);
char *int_to_string(int value,char *result,int base);
long calc_frame_size(struct task *task_list,int size);
DynamicArray generate_valid_frames(int min_frame_length,struct task *task_list,int size);
long calc_final_frame_length(struct task *task_list,int n,DynamicArray *valid_frame_size_list);
long check_valid_max_number(struct task *task_list,int n,double frame_length);
int calc_max_period(struct task *task_list,int size);
int calc_max_exec_time(struct task *task_list,int size);
double calc_hyperperiod(double arr[],int size);
double array_lcm_double(double arr[],int n);
double array_gcd_double(double arr[],int n);
double gcd_double(double a,double b);
double gcd_double(double a,double b);
extern long hyperperiod;
