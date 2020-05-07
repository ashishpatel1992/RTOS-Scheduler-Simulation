#ifndef SCHED_QUEUE_H_
#define SCHED_QUEUE_H_
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
  
void queue_sort(struct Queue *q);
void qnode_sort(struct QNode *q_arr,int queue_size);
struct QNode deQueue(struct Queue *q);
void enQueue(struct Queue *q,long task_id,long deadline);
struct Queue *createQueue();
struct QNode *newNode(long task_id,long deadline);
#endif