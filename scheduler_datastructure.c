#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int *data;
    size_t used;
    size_t size;

}DynamicArray;

void DynamicArray_init(DynamicArray *a, size_t size){
    a->data = (int *) malloc( size* sizeof(int));
    a->size = size;
    a->used = 0;
}

void DynamicArray_insert(DynamicArray *a, int value){
    if(a->used == a->size){
        a->size = a->size *2;
        a->data = (int *)realloc(a->data, a->size * sizeof(int));
    }
    a->data[a->used] = value;
    a->used++;

}
void DynamicArray_free(DynamicArray *a) {
  free(a->data);
  a->data = NULL;
  a->used = a->size = 0;
}
