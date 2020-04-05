/**
 * @file sched_dynamicarray.c
 * @author Ashish Patel (ashishpatel.1992@gmail.com)
 * @brief Array that grows dynamically
 * @version 1.0
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include<stdio.h>
#include<stdlib.h>

/**
 * @brief Dynamic array datatype that stores integer type data
 * 
 */
typedef struct{
    int *data;
    size_t used;
    size_t size;

}DynamicArray;
/**
 * @brief Creates the integer type DynamicArray, usually used for taking queue and sorting it
 * 
 * @param a Dynamic Array
 * @param size 
 */
void DynamicArray_init(DynamicArray *a, size_t size){
    a->data = (int *) malloc( size* sizeof(int));
    a->size = size;
    a->used = 0;
}
/**
 * @brief Inserts an element into DynamicArray which grows automatically upon insertion. Similar to vector.
 * 
 * @param a Dynamic Array
 * @param value element to be inserted in Dynamic Array
 */
void DynamicArray_insert(DynamicArray *a, int value){
    if(a->used == a->size){
        a->size = a->size *2;
        a->data = (int *)realloc(a->data, a->size * sizeof(int));
    }
    a->data[a->used] = value;
    a->used++;

}
/**
 * @brief Release the memorry allocated to the DynamicArray
 * 
 * @param a Dynamic Array
 */
void DynamicArray_free(DynamicArray *a) {
  free(a->data);
  a->data = NULL;
  a->used = a->size = 0;
}
