/**
 * @file sched_queue.c
 * @author Ashish Patel (ashishpatel.1992@gmail.com)
 * @brief Queue for QNode type datatype
 * @version 1.0
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include<stdio.h>
#include<stdlib.h>

/**
 * @brief A linked list (LL) node to store a task_id and their deadline.
 *
 * 
 */
struct QNode { 
    long task_id;
    long deadline;
    struct QNode* next; 
}; 
  
/**
 * @brief The queue, front stores the front node of LL and rear stores the 
 *         last node of LL 
 * 
 */
struct Queue { 
    struct QNode *front, *rear; 
    long size;
}; 
  
/**
 * @brief Create a new linked list node. 
 * 
 * @param task_id 
 * @param deadline 
 * @return struct QNode* 
 */
struct QNode* newNode(long task_id,long deadline) 
{ 
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode)); 
    temp->task_id = task_id;
    temp->deadline = deadline; 
    temp->next = NULL; 
    return temp; 
} 
  
/**
 * @brief Create an empty queue 
 * 
 * @return struct Queue* 
 */
struct Queue* createQueue() 
{ 
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue)); 
    q->front = q->rear = NULL;
    q->size =0; 
    return q; 
} 
  
/**
 * @brief Insert an element into queue
 * 
 * @param q 
 * @param task_id 
 * @param deadline 
 */
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

// void insertAtQueueFront(struct Queue* q, long task_id, long deadline) 
// { 
//     // Create a new LL node 
//     struct QNode* temp = newNode(task_id,deadline); 
    
//     // If queue is empty, then new node is front and rear both 
//     if (q->rear == NULL) { 
//         q->front = q->rear = temp; 
//         q->size=1;
//         return; 
//     } 
  
//     // Add the new node at the end of queue and change rear 
//     temp->next = q->front;
//     q->front = temp;

//     // q->rear->next = temp; 
//     // q->rear = temp; 
//     q->size++;
// } 

/**
 * @brief Remove an element from queue
 * 
 * @param q 
 * @return struct QNode 
 */
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
/**
 * @brief A utility to sort QNode type datatype based on its deadline
 * 
 * @param q_arr 
 * @param queue_size 
 */
void qnode_sort(struct QNode q_arr[], int queue_size) 
{ 
    // printf("Insertion Sort");
    struct QNode key;
    int j;
    
    for (int i = 1; i < queue_size; i++) { 
        key = q_arr[i]; 
        j = i - 1; 

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

/**
 * @brief A queue sorting function that sorts the queue in ascending order based on task's deadline with the help of qnode_sort
 * 
 * @param q input queue that needs to be sorted
 */
void queue_sort(struct Queue *q){
    
    long queue_size = q->size;
    struct QNode q_arr[queue_size];

    // printf("\nBefore Sorting: \n");
    for(int i=0;i<queue_size;i++){
        q_arr[i] = deQueue(q);
        // printf("(%ld,%ld) ",q_arr[i].task_id, q_arr[i].deadline);
    }
    
    qnode_sort(q_arr,queue_size);
    
    // printf("\n After Sorting: \n");
    
    // printf("\n");
    
    for(long i=queue_size-1;i>=0;i--){
        enQueue(q,q_arr[i].task_id,q_arr[i].deadline);
        // printf("(%ld,%ld) ",q_arr[i].task_id, q_arr[i].deadline);
    }
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