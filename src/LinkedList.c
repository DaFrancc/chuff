//
// Created by dafrancc on 12/30/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../include/LinkedList.h"
#include "../include/LinkedListNode.h"
#include "../include/LLIterator.h"

LinkedList* linkedlist_create() {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}

void linkedlist_push_back(LinkedList* list, TreeNode* val) {
    if(list == NULL) {
        errno = EINVAL;
        perror("Error: Arguments may not be NULL");
        fprintf(stderr, "Error code: %d\n", errno);
        return;
    }

    LinkedListNode* temp = linkedlistnode_create(NULL, val, NULL);

    if(list->size == 0) {
        list->head = temp;
        list->last = temp;
    }
    else {
        list->last->next = temp;
        temp->prev = list->last;
        list->last = temp;
    }

    list->size++;
}

TreeNode* linkedlist_pop_back(LinkedList* list) {
    if(list == NULL) {
        errno = EINVAL;
        perror("Error: Arguments may not be NULL");
        fprintf(stderr, "Error code: %d\n", errno);
        return 0;
    }

    if(list->size == 0) {
        errno = EINVAL;
        perror("Error: Cannot pop on empty list");
        fprintf(stderr, "Error code: %d\n", errno);
        return 0;
    }

    list->size--;

    TreeNode* result = list->last->data;

    free(list->last);

    list->last = NULL;

    if(list->size == 0) {
        list->head = NULL;
    }

    return result;
}

void linkedlist_push_front(LinkedList* list, TreeNode* val) {
    if(list == NULL) {
        errno = EINVAL;
        perror("Error: Arguments may not be NULL");
        fprintf(stderr, "Error code: %d\n", errno);
        return;
    }

    LinkedListNode* temp = linkedlistnode_create(NULL, val, NULL);

    if(list->size == 0) {
        list->head = temp;
        list->last = temp;
    }
    else {
        list->head->prev = temp;
        temp->next = list->head;
        list->head = temp;
    }

    list->size++;
}

TreeNode* linkedlist_pop_front(LinkedList* list) {
    if(list == NULL) {
        errno = EINVAL;
        perror("Error: Arguments may not be NULL");
        fprintf(stderr, "Error code: %d\n", errno);
        return 0;
    }

    if(list->size == 0) {
        errno = EINVAL;
        perror("Error: Cannot pop on empty list");
        fprintf(stderr, "Error code: %d\n", errno);
        return 0;
    }

    list->size--;

    TreeNode* result = list->head->data;

    free(list->head);

    list->head = NULL;

    if(list->size == 0) {
        list->last = NULL;
    }

    return result;
}

void linkedlist_print(const LinkedList* list) {
    const LinkedListNode* n = list->head;

    while(n != NULL) {
        printf("%p\n", treenode_tostring(n->data));
        n = n->next;
    }
}

LinkedList* linkedlist_clone(const LinkedList* list) {
    LinkedList* res = malloc(sizeof(LinkedList));
    res->head = NULL;
    res->last = NULL;
    res->size = list->size;

    LLIterator* it = lliterator_make(list);

    while(lliterator_hasnext(it)) {
        linkedlist_push_back(res, lliterator_next(it));
    }

    return res;
}

void linkedlist_free(LinkedList* list) {
    LinkedListNode* n = list->head;

    while(n != NULL) {
        LinkedListNode* temp = n;
        n = n->next;
        free(temp);
    }

    free(list);
}
