//
// Created by dafrancc on 12/31/23.
//

#include <stdlib.h>
#include <stdio.h>

#include "../include/HashMap.h"

#include <string.h>

HashMap* hashmap_make(const size_t size) {
    HashMap* map = malloc(sizeof(HashMap));
    map->size = size;
    map->count = 0;
    map->items = calloc(map->size, sizeof(HashEntry*));

    for(int i = 0; i < map->size; ++i) {
        map->items[i] = NULL;
    }

    return map;
}

void hashmap_put(const HashMap* map, const int key, const char* value) {
    if(map->items[key]) {
        free(map->items[key]);
    }
    map->items[key] = hashentry_make(key, value);
}
int hashmap_containskey(const HashMap* map, const int key) {
    return map->items[key] != NULL;
}
char* hashmap_get(const HashMap* map, const int key) {
    return map->items[key]->value;
}
int* hashmap_keyset(const HashMap* map) {
    int* keyset = calloc(map->count, sizeof(int));
    int i = 0;
    for (int j = 0; j < map->size; ++j) {
        if(map->items[j]) {
            keyset[i] = map->items[j]->key;
            ++i;
        }
    }
    return keyset;
}

void hashmap_free(HashMap* map) {
    for (int i = 0; i < map->size; ++i) {
        HashEntry* entry = map->items[i];
        if(entry) {
            hashentry_free(entry);
        }
    }

    free(map->items);
    free(map);
}

void hashmap_print(const HashMap* map) {
    printf("{%d=%s", map->items[0]->key, map->items[0]->value);
    for (int i = 1; i < map->size; ++i) {
        if(map->items[i]) {
            printf(", %d=%s", map->items[i]->key, map->items[i]->value);
        }
    }
    printf("}\n");
}