//
// Created by dafrancc on 12/30/23.
//

#ifndef LLITERATOR_H
#define LLITERATOR_H

#include "LinkedList.h"

typedef struct LLIterator {
    LinkedList* list;
    LinkedListNode* next;
    int nextIndex;
    LinkedListNode* lastReturned;
} LLIterator;

LLIterator* lliterator_make(LinkedList* list);
int lliterator_hasnext(const LLIterator* it);
TreeNode* lliterator_next(LLIterator* it);
int lliterator_hasprevious(const LLIterator* it);
TreeNode* lliterator_previous(LLIterator* it);
void lliterator_add(LLIterator* it, TreeNode* val);
// void lliterator_remove(LLIterator* it);

#endif //LLITERATOR_H
