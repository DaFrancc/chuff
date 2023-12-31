//
// Created by dafrancc on 12/30/23.
//
#include <stdlib.h>
#include <math.h>

#include "../include/TreeNode.h"

#include <stdio.h>

TreeNode* treenode_make(const int value, const int frequency) {
    TreeNode* tn = malloc(sizeof(TreeNode));

    tn->value = value;
    tn->frequency = frequency;

    return tn;
}

int treenode_compare(const TreeNode* a, const TreeNode* b) {
    return a->frequency - b->frequency;
}

static int lengthofint(int val) {
    if(val == 0) {
        return 1;
    }

    return (int)log10(fabs(val)) + 1;
}

char* treenode_tostring(const TreeNode* tn) {
    // 27 characters + EOL char + length of freq + 2 * length of val
    char* str = malloc(28 + lengthofint(tn->frequency) + 2 * lengthofint(tn->value));
    sprintf(str, "(%d, %c as char, %d value as int)", tn->frequency, (char)tn->value, tn->value);
    return str;
}

int treenode_isleaf(const TreeNode* tn) {
    return !tn->left && !tn->right;
}