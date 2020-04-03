#include<stdio.h>
#include"scheduler_ds_test.c"


int main(int argc, char const *argv[])
{
    DynamicArray la;
    DynamicArray_init(&la,20,sizeof(int));
    for (size_t i = 0; i < 5; i++)
    {
        DynamicArray_insert(&la,i);
        // printf("\n%d" ,(int)la.array[i]);
    }
    
    return 0;
}
