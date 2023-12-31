//
// Created by dafrancc on 12/31/23.
//
#include <stdlib.h>

#include "../include/HashEntry.h"

#include <string.h>

HashEntry* hashentry_make(const int key, const char* value){
    HashEntry* he = malloc(sizeof(HashEntry));
    he->key = key;
    he->value = malloc(strlen(value) + 1);
    strcpy(he->value, value);
    return he;
}

void hashentry_free(HashEntry* he) {
    free(he->value);
    free(he);
}