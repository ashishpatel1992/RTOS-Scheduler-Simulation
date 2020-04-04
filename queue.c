// C program for array implementation of queue 
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include "task.c"
  
// A structure to represent a queue 
struct Queue 
{ 
    int front, rear, size; 
    unsigned capacity; 
    struct task* array;
    // int* array; 
}; 
struct task nulltask;
// nulltask. = 0;
// function to create a queue of given capacity.  
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity) 
{ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1;  // This is important, see the enqueue 
    queue->array = (struct task*) malloc(queue->capacity * sizeof(struct task)); 
    return queue; 
} 
  
// Queue is full when size becomes equal to the capacity  
int isFull(struct Queue* queue) 
{  return (queue->size == queue->capacity);  } 
  
// Queue is empty when size is 0 
int isEmpty(struct Queue* queue) 
{  return (queue->size == 0); } 
  
// Function to add an item to the queue.   
// It changes rear and size 
int enqueue(struct Queue* queue, struct task item) 
{ 
    if (isFull(queue)) {
        printf("\nQueue is FULL");
        return 0; //QUEUE FULL 
    }
    queue->rear = (queue->rear + 1)%queue->capacity; 
    queue->array[queue->rear] = item; 
    queue->size = queue->size + 1; 
    // printf("%d enqueued to queue\n", item); 
    return 1; // SUCCESSFULLY INSERTED IN QUEUE
} 
  
// Function to remove an item from queue.  
// It changes front and size 
struct task dequeue(struct Queue* queue) 
{ 
    
    if (isEmpty(queue)) 
        return nulltask; 
    struct task item = queue->array[queue->front]; 
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
} 
  
// Function to get front of queue 
struct task front(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return nulltask; 
    return queue->array[queue->front]; 
} 
  
// Function to get rear of queue 
struct task rear(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return nulltask; 
    return queue->array[queue->rear]; 
} 