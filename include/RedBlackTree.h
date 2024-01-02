//
// Created by dafrancc on 12/31/23.
//

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <stddef.h>
#include "RBNode.h"

typedef struct RedBlackTree {
    RBNode* root;
    size_t size;
} RedBlackTree;

RedBlackTree* redblacktree_make(size_t size);
int redblacktree_put(RedBlackTree* map, int key, int value);
int redblacktree_containskey(const RedBlackTree* map, int key);
char* redblacktree_get(const RedBlackTree* map, int key);
int* redblacktree_keyset(const RedBlackTree* map);
RBNode** redblacktree_entries(RedBlackTree* map);
void redblacktree_free(RedBlackTree* map);
void redblacktree_print(const RedBlackTree* map);

#endif //REDBLACKTREE_H
