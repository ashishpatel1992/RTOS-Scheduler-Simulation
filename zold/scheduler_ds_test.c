#include<stdio.h>
#include<stdlib.h>
typedef struct{
    void *array;
    size_t used;
    size_t size;
    size_t datatype_size;
}DynamicArray;
union Dynamic
{
    int i;
    float f;
};

void DynamicArray_init(DynamicArray *a, size_t size,size_t datatype_size){
    a->array = (void *) malloc( size* datatype_size);
    a->size = size;
    a->used = 0;
    a->size = datatype_size;
}

void DynamicArray_insert(DynamicArray *a, int value){
    if(a->used == a->size){
        a->size = a->size *2;
        a->array = (void *)realloc(a->array, a->size * a->datatype_size);
    }
    void *t_val = (void *)value;
    a->array[a->used] = t_val;
    a->used++;

}
void DynamicArray_free(DynamicArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
