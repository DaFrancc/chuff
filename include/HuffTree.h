//
// Created by dafrancc on 12/31/23.
//

#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "PriorityQueue.h"
#include "TreeNode.h"


typedef struct HuffTree {
    TreeNode* root;
} HuffTree;

HuffTree* hufftree_make_from_pq(PriorityQueue* pq);
HuffTree* hufftree_make_from_treenode(TreeNode* node);
int hufftree_get_val(char* path, const TreeNode* n);


#endif //HUFFTREE_H
