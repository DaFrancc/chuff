//
// Created by dafrancc on 12/30/23.
//

#include "../include/PriorityQueue.h"

#include "../include/LLIterator.h"

PriorityQueue* priorityqueue_make(LinkedList* list) {
    PriorityQueue* pq = malloc(sizeof(PriorityQueue));
    pq->con = list;
    return pq;
}

void priorityqueue_enqueue(PriorityQueue* pq, TreeNode* val) {
    LLIterator* it = lliterator_make(pq->con);

    if(pq->con->size == 0) {
        linkedlist_push_back(pq->con, val);
    }
    else {
        while(lliterator_hasnext(it)) {
            if(treenode_compare(val, lliterator_next(it)) < 0) {
                lliterator_previous(it);
                break;
            }
        }

        lliterator_add(it, val);
    }
}

TreeNode* priorityqueue_front(const PriorityQueue* pq) {
    return pq->con->head->data;
}

PriorityQueue* priorityqueue_clone(const PriorityQueue* pq) {
    PriorityQueue* res = malloc(sizeof(PriorityQueue));
    res->con = pq->con;
    return res;
}

TreeNode* priorityqueue_dequeue(PriorityQueue* pq) {
    return linkedlist_pop_front(pq->con);
}

LinkedList* priorityqueue_free(PriorityQueue* pq) {
    free(pq);
}