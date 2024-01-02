//
// Created by dafrancc on 12/31/23.
//

#include <stdlib.h>
#include "../include/RBNode.h"

RBNode* rbnode_make(Color color, int key, int value) {
    RBNode* n = malloc(sizeof(RBNode));

    n->color = color;
    n->key = key;
    n->value = value;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void rbnode_copy(RBNode* dst, RBNode* src) {
    dst->color = src->color;
    dst->key = src->key;
    dst->value = src->value;
    dst->left = src->left;
    dst->right = src->right;
}