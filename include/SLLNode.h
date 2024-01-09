//
// Created by dafrancc on 1/8/24.
//

#ifndef CHUFF_SLLNODE_H
#define CHUFF_SLLNODE_H

typedef struct SLLNode {
    struct SLLNode* prev;
    char* data;
    struct SLLNode* next;
} SLLNode;

SLLNode* sllnode_create(SLLNode* prev, char* data, SLLNode* next);
int sllnode_equals(const SLLNode* a, const SLLNode* b);
int sllnode_compare(const SLLNode* a, const SLLNode* b);
void sllnode_free(SLLNode* node);

#endif //CHUFF_SLLNODE_H
