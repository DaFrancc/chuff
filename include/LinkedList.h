//
// Created by dafrancc on 12/30/23.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../include/LinkedListNode.h"
#include <stdlib.h>

typedef struct LinkedList {
    LinkedListNode* head;
    LinkedListNode* last;
    size_t size;
} LinkedList;

LinkedList* linkedlist_create();
void linkedlist_push_back(LinkedList* list, TreeNode* val);
TreeNode* linkedlist_pop_back(LinkedList* list);
void linkedlist_push_front(LinkedList* list, TreeNode* val);
TreeNode* linkedlist_pop_front(LinkedList* list);
void linkedlist_print(const LinkedList* list);
void linkedlist_free(LinkedList* list);

#endif //LINKEDLIST_H
