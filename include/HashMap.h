//
// Created by dafrancc on 12/31/23.
//

#ifndef HASHMAP_H
#define HASHMAP_H

#include "HashEntry.h"

typedef struct HashMap {
    HashEntry** items;
    int size;
    int count;
} HashMap;

HashMap* hashmap_make(size_t size);
void hashmap_put(const HashMap* map, int key, const char* value);
int hashmap_containskey(const HashMap* map, int key);
char* hashmap_get(const HashMap* map, int key);
int* hashmap_keyset(const HashMap* map);
HashEntry** hashmap_entries(HashMap* map);
void hashmap_free(HashMap* map);
void hashmap_print(const HashMap* map);

#endif //HASHMAP_H
