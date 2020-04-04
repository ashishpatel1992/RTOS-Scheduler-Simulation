/**
 * TEST MODULE
 * Author: Ashish Patel
 **/
#include<stdio.h>
#include<stdlib.h>
// A linked list (LL) node to store a queue entry 
struct QNode { 
    long task_id;
    long deadline;
    struct QNode* next; 
}; 
  
// The queue, front stores the front node of LL and rear stores the 
// last node of LL 
struct Queue { 
    struct QNode *front, *rear; 
    long size;
}; 
  
// A utility function to create a new linked list node. 
struct QNode* newNode(long task_id,long deadline) 
{ 
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode)); 
    temp->task_id = task_id;
    temp->deadline = deadline; 
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
void enQueue(struct Queue* q, long task_id, long deadline) 
{ 
    // Create a new LL node 
    struct QNode* temp = newNode(task_id,deadline); 
    
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

void insertAtQueueFront(struct Queue* q, long task_id, long deadline) 
{ 
    // Create a new LL node 
    struct QNode* temp = newNode(task_id,deadline); 
    
    // If queue is empty, then new node is front and rear both 
    if (q->rear == NULL) { 
        q->front = q->rear = temp; 
        q->size=1;
        return; 
    } 
  
    // Add the new node at the end of queue and change rear 
    temp->next = q->front;
    q->front = temp;

    // q->rear->next = temp; 
    // q->rear = temp; 
    q->size++;
} 

// Function to remove a key from given queue q 
struct QNode deQueue(struct Queue* q) 
{ 
    struct QNode deleted_node;
    
    // If queue is empty, return NULL. 
    if (q->front == NULL) 
        return deleted_node; 
  
    // Store previous front and move front one node ahead 
    struct QNode* temp = q->front; 
    deleted_node = *temp;
    q->front = q->front->next; 
    q->size--;
    // If front becomes NULL, then change rear also as NULL 
    if (q->front == NULL) {
        q->rear = NULL; 
        q->size=0;
    }
    
    free(temp); 
    deleted_node.next = NULL;
    return deleted_node;
}

/* Function to sort an array using insertion sort*/
void insertionSort(struct QNode q_arr[], int queue_size) 
{ 
    printf("Insertion Sort");
    struct QNode key;
    int j;
    
    for (int i = 1; i < queue_size; i++) { 
        key = q_arr[i]; 
        j = i - 1; 

        // while (j >= 0 && q_arr[j].deadline > key.deadline) {  // (q_arr[j].deadline > key.deadline) is problem
        while (j >= 0 && q_arr[j].deadline > key.deadline) { 
            q_arr[j + 1] = q_arr[j]; 
            j = j - 1; 
        } 
        q_arr[j + 1] = key; 
    } 

    for(int i=0;i<queue_size/2;i++){
        struct  QNode node;
        node = q_arr[i];
        q_arr[i] = q_arr[queue_size-i-1];
        q_arr[queue_size-i-1] = node;
    }
    // fprintf(stderr,"...");
} 

// void generic_sort(struct QNode q_a)
void queue_sort(struct Queue *q){
    // printf("Size: >> %ld",q->size);
    // return ;
    long queue_size = q->size;
    struct QNode q_arr[queue_size];

    printf("\nBefore Sorting: \n");
    for(int i=0;i<queue_size;i++){
        q_arr[i] = deQueue(q);
        printf("(%ld,%ld) ",q_arr[i].task_id, q_arr[i].deadline);
    }
    
    insertionSort(q_arr,queue_size);
    
    printf("\n After Sorting: \n");
    // for(int i=0;i<queue_size;i++){
    //     printf("(%ld,%ld) ",q_arr[i].task_id, q_arr[i].deadline);
    // }
    printf("\n");
    // int i;
    for(long i=queue_size-1;i>=0;i--){
        enQueue(q,q_arr[i].task_id,q_arr[i].deadline);
        printf("(%ld,%ld) ",q_arr[i].task_id, q_arr[i].deadline);
    }
    // printf("(%ld,%ld) ",q_arr[i].task_id, q_arr[i].deadline);
    // for(int i=queue_size-1;i>=0;i--){
    //     enQueue(q,q_arr[i].task_id,q_arr[i].deadline);
    //     // q_arr[i] = deQueue(q);
    //     // printf("(%ld,%ld) ",q_arr[i].task_id, q_arr[i].deadline);
    // }
    // printf("\nQz %ld ",queue_size);
    // printf("\ns:%ld",q->size);
}

// Test Driver Program to test Module 
// int main() 
// { 
//     struct Queue* q = createQueue(); 
    
//     enQueue(q,1,2); // queue, task_id, deadline
//     enQueue(q, 2,4);
//     enQueue(q, 1,1); 
//     enQueue(q, 1,2); 
//     deQueue(q);
     
//     enQueue(q, 2,1); 
//     //traverseQueue(q);
//     enQueue(q, 2,2); 
//     enQueue(q, 2,3); 
    
//     deQueue(q); 
//     // deQueue(q);
//     // deQueue(q);
//     // deQueue(q);
//     // deQueue(q);
//     // deQueue(q);
//     // deQueue(q);
//     // enQueue(q, 2,3); 
//     insertAtQueueFront(q,4,6);
//     printf("%ld",q->size);
//     if(q->size !=0){
//         printf("\nQueue Front : %ld,%ld \n", q->front->task_id,q->front->deadline); 
//         printf("Queue Rear : %ld,%ld\n", q->rear->task_id,q->rear->deadline); 
//         printf("\nQueue Size is %ld",q->size);
//     }
    
    
//     queue_sort(q);
//     long queue_size = q->size;
//     for(int i=0;i<queue_size;i++){
//         struct QNode n = deQueue(q);
//         printf("\n val (%ld,%ld) ",n.task_id,n.deadline);
//     }
//     // while(q->front){
//     //     printf("%ld,%ld ,",q->front->task_id,q->front->job_id);
//     //     deQueue(q);
//     // }
//     // printf("\nQSize %ld\n",q->size);
//     printf("\n");
//     return 0; 
// } 