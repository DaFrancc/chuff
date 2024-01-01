//
// Created by dafrancc on 12/31/23.
//

#ifndef RBNODE_H
#define RBNODE_H

typedef enum Color {
    RED,
    BLACK
} Color;

typedef struct RBNode {
    Color color;
    int key;
    int value;
    struct RBNode* left;
    struct RBNode* right;
} RBNode;

RBNode* rbnode_make(Color color, int key, int value);

#endif //RBNODE_H
