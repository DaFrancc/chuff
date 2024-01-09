//
// Created by dafrancc on 1/8/24.
//

#include <errno.h>
#include <stdio.h>
#include "../include/StringLL.h"
#include "../include/SLLNode.h"

StringLL* stringll_create() {
    StringLL* list = malloc(sizeof(StringLL));
    list->head = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}
void stringll_push_back(StringLL* list, char* val) {
    if(list == NULL) {
        errno = EINVAL;
        perror("Error: Arguments may not be NULL");
        fprintf(stderr, "Error code: %d\n", errno);
        return;
    }

    SLLNode* temp = sllnode_create(NULL, val, NULL);

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
char* stringll_pop_back(StringLL* list) {
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

    char* result = list->last->data;

    free(list->last);

    list->last = NULL;

    if(list->size == 0) {
        list->head = NULL;
    }

    return result;
}
void stringll_push_front(StringLL* list, char* val) {
    if(list == NULL) {
        errno = EINVAL;
        perror("Error: Arguments may not be NULL");
        fprintf(stderr, "Error code: %d\n", errno);
        return;
    }

    SLLNode* temp = sllnode_create(NULL, val, NULL);

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
char* stringll_pop_front(StringLL* list) {
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

    char* result = list->head->data;

    free(list->head);

    list->head = NULL;

    if(list->size == 0) {
        list->last = NULL;
    }

    return result;
}
void stringll_free(StringLL* list) {
    SLLNode* n = list->head;

    while(n != NULL) {
        SLLNode* temp = n;
        n = n->next;
        sllnode_free(temp);
    }

    free(list);
}