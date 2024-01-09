//
// Created by dafrancc on 1/8/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/SLLNode.h"

SLLNode* sllnode_create(SLLNode* prev, char* data, SLLNode* next) {
    SLLNode* n = malloc(sizeof(SLLNode));
    n->prev = NULL;
    n->data = data;
    n->next = next;
    return n;
}

int sllnode_equals(const SLLNode* a, const SLLNode* b) {
    if(a == NULL || b == NULL) {
        errno = EINVAL;
        perror("Error: Cannot accept null arguments");
        fprintf(stderr, "Error code: %d\n", errno);
        return -1;
    }

    return strcmp(a->data, b->data) == 0;
}

int sllnode_compare(const SLLNode* a, const SLLNode* b) {
    if(a == NULL || b == NULL) {
        errno = EINVAL;
        perror("Error: Cannot accept null arguments");
        fprintf(stderr, "Error code: %d\n", errno);
        return -1;
    }

    return strcmp(a->data, b->data);
}

void sllnode_free(SLLNode* node) {
    free(node->data);
    free(node);
}
