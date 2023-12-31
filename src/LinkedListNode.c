//
// Created by dafrancc on 12/30/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/LinkedListNode.h"

LinkedListNode* linkedlistnode_create(LinkedListNode* prev, TreeNode* data, LinkedListNode* next) {
    LinkedListNode* n = malloc(sizeof(LinkedListNode));
    n->prev = NULL;
    n->data = data;
    n->next = next;
    return n;
}

int linkedlistnode_equals(const LinkedListNode* a, const LinkedListNode* b) {
    if(a == NULL || b == NULL) {
        errno = EINVAL;
        perror("Error: Cannot accept null arguments");
        fprintf(stderr, "Error code: %d\n", errno);
        return -1;
    }

    return a->data == b->data;
}

int linkedlistnode_compare(const LinkedListNode* a, const LinkedListNode* b) {
    if(a == NULL || b == NULL) {
        errno = EINVAL;
        perror("Error: Cannot accept null arguments");
        fprintf(stderr, "Error code: %d\n", errno);
        return -1;
    }

    return treenode_compare(a->data, b->data);
}


