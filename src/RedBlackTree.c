//
// Created by dafrancc on 12/31/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/RedBlackTree.h"

RedBlackTree * redblacktree_make(const size_t size) {
    RedBlackTree* tree = malloc(sizeof(RedBlackTree));
    tree->root = NULL;
    tree->size = size;

    return tree;
}

static void case3(RBNode* node) {
    if(node->left->color == RED && node->right->color == RED) {
        node->left->color = BLACK;
        node->right->color = BLACK;
        node->color = RED;
    }
}

//static RBNode* put_helper(RedBlackTree* tree, RBNode* currNode, RBNode* newNode) {
//    if(!currNode) {
//        tree->size++;
//        return newNode;
//    }
//
//    case3(currNode); // prevent case 3
//
//    int comparison = newNode->key - currNode->key;
//
//    if(comparison > 0) {
//        currNode->left = put_helper(tree, currNode->right, newNode);
//    }
//    else if(comparison < 0) {
//        currNode->right = put_helper(tree, currNode->left, newNode);
//    }
//    else {
//        newNode->left = currNode->left;
//        newNode->right = currNode->right;
//        free(currNode);
//    }
//
//    // case 1
////    case1(tree, )
//    // case 2
//    tree->root->color = BLACK;
//
//    return newNode;
//}
//
//int redblacktree_put(RedBlackTree* tree, int key, int value) {
//    RBNode* newNode = rbnode_make(RED, key, value);
//
//    if(tree->size == 0) {
//        tree->root = newNode;
//        newNode->color = BLACK;
//        return 1;
//    }
//
//    size_t oldSize = tree->size;
//    tree->root = put_helper(tree, tree->root, newNode);
//
//    return tree->size != oldSize;
//}

// 0 = left-right, 1 = right-left
static void case2(RBNode *node, int direction) {
    RBNode* t1 = malloc(sizeof(RBNode));
    RBNode* t2 = malloc(sizeof(RBNode));
    if(direction) {
        if(node->right->color == RED && node->right->left->color == RED) {
            t1 = node->right;
            t2 = node->right->left->right;
            node->right = node->left->left;
            node->right = t1;
            node->right->right->left = t2;
        }
    }
    else {
        if(node->left->color == RED && node->left->right->color == RED) {
            t1 = node->left;
            t2 = node->left->right->left;
            node->left = node->left->right;
            node->left = t1;
            node->left->left->right = t2;
        }
    }
    free(t1);
    free(t2);
}

// 0 = left-left, 1 = right-right
static void case1(RBNode *node, int direction) {
    RBNode* t1 = malloc(sizeof(RBNode));
    RBNode* t2 = malloc(sizeof(RBNode));
    RBNode* t3 = malloc(sizeof(RBNode));
    if(direction) {
        if(node->right->color == RED && node->right->right->color == RED) {
            t1 = node->right;
            t2 = node->right->left->right;
            node->right = node->left->left;
            node->right = t1;
            node->right->right->left = t2;
        }
    }
    else {
        if(node->left->color == RED && node->left->left->color == RED) {
            rbnode_copy(t1, node);
            rbnode_copy(t2, node->left->right);
            rbnode_copy(t3, node->left);
            free(node);
            rbnode_copy(node, t1->left);

            t1->left = t2;

//            node->left = node->left->right;
//            node->left = t1;
//            node->left->left->right = t2;
        }
    }
    free(t1);
    free(t2);
}

// 0 = size unchanged, 1 = size changed, 2 = check case 2 & 1, 3 = intermediate step
static int put_helper(RedBlackTree* tree, RBNode* currNode, RBNode* newNode) {
    case3(currNode);

    int comparison = newNode->key - currNode->key;
    int returnCode = 0;

    if(comparison > 0) {
        if(currNode->left) {
            int code = put_helper(tree, currNode->left, newNode);
            if(code == 2) {
                case2(currNode, 0);
                case1(currNode, 0);
            }
        }
        else {
            currNode->left = newNode;
        }
    }
    else if(comparison < 0) {
        if(currNode->right) {
            int code = put_helper(tree, currNode->right, newNode);
            if(code == 2) {
                case2(currNode, 1);
                case1(currNode, 1);
            }
        }
        else {
            currNode->right = newNode;
        }
    }
    else {
        newNode->left = currNode->left;
        newNode->right = currNode->right;
        const Color oldColor = currNode->color;
        rbnode_copy(currNode, newNode);
        newNode->color = oldColor;
    }

    return returnCode;
}

int redblacktree_put(RedBlackTree* tree, int key, int value) {
    RBNode* newNode = rbnode_make(RED, key, value);

    if(tree->size == 0) {
        tree->root = newNode;
        newNode->color = BLACK;
        return 1;
    }

    size_t oldSize = tree->size;
    tree->size += put_helper(tree, tree->root, newNode);
    free(newNode);

    return tree->size != oldSize;
}

//int redblacktree_containskey(const RedBlackTree* tree, const int key) {
//    return tree->items[key] != NULL;
//}
//char* redblacktree_get(const RedBlackTree* tree, const int key) {
//    return tree->items[key]->value;
//}
//int* redblacktree_keyset(const RedBlackTree* tree) {
//    int* keyset = calloc(tree->size, sizeof(int));
//    int i = 0;
//    for (int j = 0; j < tree->size; ++j) {
//        if(tree->items[j]) {
//            keyset[i] = tree->items[j]->key;
//            ++i;
//        }
//    }
//    return keyset;
//}
//
//RBNode** entries_helper(RBNode* n)
//
//RBNode** redblacktree_entries(RedBlackTree* map) {
//    return entries_helper(map->root);
//}
//
//void redblacktree_free(RedBlackTree* tree) {
//    for (int i = 0; i < tree->size; ++i) {
//        RBNode* entry = tree->items[i];
//        if(entry) {
//            free(entry);
//        }
//    }
//
//    free(tree->items);
//    free(tree);
//}
//
//void redblacktree_print(const RedBlackTree* tree) {
//    printf("{%d=%s", tree->items[0]->key, tree->items[0]->value);
//    for (int i = 1; i < tree->size; ++i) {
//        if(tree->items[i]) {
//            printf(", %d=%s", tree->items[i]->key, tree->items[i]->value);
//        }
//    }
//    printf("}\n");
//}