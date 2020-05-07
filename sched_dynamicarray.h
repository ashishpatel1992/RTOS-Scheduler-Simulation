#ifndef SCHED_DYNAMICARRAY_H_
#define SCHED_DYNAMICARRAY_H_
#include"sched_dynamicarray.c"
struct DynamicArray;
void DynamicArray_free(DynamicArray *a);
void DynamicArray_insert(DynamicArray *a,int value);
void DynamicArray_init(DynamicArray *a,size_t size);
#endif
