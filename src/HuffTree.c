//
// Created by dafrancc on 12/31/23.
#include <stdlib.h>
#include <string.h>

#include "../include/HuffTree.h"


#define ZERO_ASCII 48

/**
 * \brief Internal function to create tree, not to be called outside of file
 * \param pq PriorityQueue to make tree from. Will be consumed after call is made
 * \return Returns the root node for a HuffTree
 */
static TreeNode* createTree(PriorityQueue* pq) {
    if(pq->con->size > 1) {
        TreeNode* t1 = priorityqueue_dequeue(pq);
        TreeNode* t2 = priorityqueue_dequeue(pq);
        TreeNode* t3 = treenode_make(0, t1->frequency + t2->frequency);
        t3->left = t1;
        t3->right = t2;

        priorityqueue_enqueue(pq, t3);

        return createTree(pq);
    }

    return priorityqueue_dequeue(pq);
}

HuffTree* hufftree_make_from_pq(PriorityQueue* pq) {
    HuffTree* hTree = malloc(sizeof(HuffTree));

    hTree->size = pq->con->size;
    hTree->root = createTree(pq);

    return hTree;
}
HuffTree* hufftree_make_from_treenode(TreeNode* node) {
    HuffTree* hTree = malloc(sizeof(HuffTree));

    hTree->root = node;

    return hTree;
}

int hufftree_get_val(char* path, const TreeNode* n) {
    if(!n) {
        free(path);
        return -1;
    }
    if(strlen(path) == 0 && treenode_isleaf(n)) {
        free(path);
        return n->value;
    }
    if(strlen(path) == 0 && !treenode_isleaf(n)) {
        free(path);
        return -1;
    }

    const char direction = path[0];

    char* newPath = calloc(strlen(path), sizeof(char));
    strncpy(newPath, path + 1, strlen(path));
    free(path);

    if(direction == ZERO_ASCII) {
        return hufftree_get_val(newPath, n->left);
    }

    return hufftree_get_val(newPath, n->right);
}