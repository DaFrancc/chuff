//
// Created by dafrancc on 12/30/23.
//

#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H
#include "TreeNode.h"

typedef struct LinkedListNode {
    struct LinkedListNode* prev;
    TreeNode* data;
    struct LinkedListNode* next;
} LinkedListNode;

LinkedListNode* linkedlistnode_create(LinkedListNode* prev, TreeNode* data, LinkedListNode* next);
int linkedlistnode_equals(const LinkedListNode* a, const LinkedListNode* b);
int linkedlistnode_compare(const LinkedListNode* a, const LinkedListNode* b);

#endif //LINKEDLISTNODE_H
