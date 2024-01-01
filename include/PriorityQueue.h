//
// Created by dafrancc on 12/30/23.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "LinkedList.h"

typedef struct PriorityQueue {
    LinkedList* con;
} PriorityQueue;

PriorityQueue* priorityqueue_make(LinkedList* list);
void priorityqueue_enqueue(PriorityQueue* pq, TreeNode* val);
TreeNode* priorityqueue_front(const PriorityQueue* pq);
PriorityQueue* priorityqueue_clone(const PriorityQueue* pq);
TreeNode* priorityqueue_dequeue(PriorityQueue* pq);

#endif //PRIORITYQUEUE_H
