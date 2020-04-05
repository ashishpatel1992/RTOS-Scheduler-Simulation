#include<stdio.h>
#include<stdlib.h>
// A linked list (LL) node to store a queue entry 
struct QNode { 
    long task_id;
    // long job_id;
    struct QNode* next; 
}; 
  
// The queue, front stores the front node of LL and rear stores the 
// last node of LL 
struct Queue { 
    struct QNode *front, *rear; 
    long size;
}; 
  
// A utility function to create a new linked list node. 
struct QNode* newNode(long task_id) 
{ 
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode)); 
    temp->task_id = task_id;
    // temp->job_id = job_id; 
    temp->next = NULL; 
    return temp; 
} 
  
// A utility function to create an empty queue 
struct Queue* createQueue() 
{ 
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue)); 
    q->front = q->rear = NULL;
    q->size =0; 
    return q; 
} 
  
// The function to add a key k to q 
void enQueue(struct Queue* q, long task_id) 
{ 
    // Create a new LL node 
    struct QNode* temp = newNode(task_id); 
    
    // If queue is empty, then new node is front and rear both 
    if (q->rear == NULL) { 
        q->front = q->rear = temp; 
        q->size=1;
        return; 
    } 
  
    // Add the new node at the end of queue and change rear 
    q->rear->next = temp; 
    q->rear = temp; 
    q->size++;
} 
  
// Function to remove a key from given queue q 
long deQueue(struct Queue* q) 
{ 
    long task_id =-1;
    // If queue is empty, return NULL. 
    if (q->front == NULL) 
        return task_id; 
  
    // Store previous front and move front one node ahead 
    struct QNode* temp = q->front; 
    task_id = temp->task_id;
    q->front = q->front->next; 
    q->size--;
    // If front becomes NULL, then change rear also as NULL 
    if (q->front == NULL) {
        q->rear = NULL; 
        q->size=0;
    }
    
    free(temp); 
    return task_id;
} 

// Driver Program to test anove functions 
// int main() 
// { 
//     struct Queue* q = createQueue(); 
//     enQueue(q, 1,1); 
//     enQueue(q, 1,2); 
//     deQueue(q);
     
//     enQueue(q, 2,1); 
//     //traverseQueue(q);
//     enQueue(q, 2,2); 
//     enQueue(q, 2,3); 
//     // deQueue(q); 
    
//     printf("\nQueue Front : %ld,%ld \n", q->front->task_id,q->front->job_id); 
//     printf("Queue Rear : %ld,%ld\n", q->rear->task_id,q->rear->job_id); 
    
//     // while(q->front){
//     //     printf("%ld,%ld ,",q->front->task_id,q->front->job_id);
//     //     deQueue(q);
//     // }
//     printf("\nQSize %ld\n",q->size);
//     return 0; 
// } 