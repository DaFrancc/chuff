//
// Created by dafrancc on 12/31/23.
//

#ifndef HASHENTRY_H
#define HASHENTRY_H

typedef struct HashEntry {
    int key;
    char* value;
} HashEntry;

HashEntry* hashentry_make(int key, const char* value);
void hashentry_free(HashEntry* he);

#endif //HASHENTRY_H
