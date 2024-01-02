//
// Created by dafrancc on 12/30/23.
//

#include "../include/LLIterator.h"

LLIterator* lliterator_make(const LinkedList* list) {
    LLIterator* lli = malloc(sizeof(LLIterator));

    lli->list = list;
    lli->next = list->size == 0 ? NULL : list->head;
    lli->nextIndex = 0;
    lli->lastReturned = NULL;

    return lli;
}
int lliterator_hasnext(const LLIterator* it) {
    return it->nextIndex < it->list->size;
}
TreeNode* lliterator_next(LLIterator* it) {
    if(lliterator_hasnext(it)) {
        it->lastReturned = it->next;
        it->next = it->next->next;
        ++it->nextIndex;
        return it->lastReturned->data;
    }

    return NULL;
}
int lliterator_hasprevious(const LLIterator* it) {
    return it->nextIndex > 0;
}
TreeNode* lliterator_previous(LLIterator* it) {
    if(lliterator_hasprevious(it)) {
        it->lastReturned = it->next = it->next == NULL ? it->list->last : it->next->prev;
        --it->nextIndex;
        return it->lastReturned->data;
    }

    return NULL;
}

void lliterator_add(LLIterator* it, TreeNode* val) {
    it->lastReturned = NULL;
    if(!it->next) {
        linkedlist_push_back(it->list, val);
    }
    else {
        if(it->next->prev) {
            LinkedListNode* lln = linkedlistnode_create(it->next->prev, val, it->next);
            it->next->prev->next = lln;
            it->next->prev = lln;
        }
        else {
            LinkedListNode* lln = linkedlistnode_create(NULL, val, it->next);
            it->list->head = lln;
            it->next->prev = lln;
        }
        ++it->nextIndex;
    }
}
// void lliterator_remove(LLIterator* it) {
//     if(!it->lastReturned) {
//         return;
//     }
//
//     LinkedListNode* n = it->lastReturned->next;
//
// }