//
// Created by dafrancc on 12/30/23.
//

#ifndef TREENODE_H
#define TREENODE_H

typedef struct TreeNode {
    int value;
    int frequency;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

/*
    Makes a TreeNode
*/
TreeNode* treenode_make(int value, int frequency);

/*
    Compares the second TreeNode to the first using the following formula:
    * a-b
*/
int treenode_compare(const TreeNode* a, const TreeNode* b);
char* treenode_tostring(const TreeNode* tn);
int treenode_isleaf(const TreeNode* tn);

#endif //TREENODE_H
