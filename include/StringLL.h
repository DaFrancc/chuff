//
// Created by dafrancc on 1/8/24.
//

#ifndef CHUFF_STRINGLL_H
#define CHUFF_STRINGLL_H

#include <stdlib.h>
#include "SLLNode.h"

typedef struct StringLL {
    SLLNode* head;
    size_t size;
    SLLNode* last;
} StringLL;

StringLL* stringll_create();
void stringll_push_back(StringLL* list, char* val);
char* stringll_pop_back(StringLL* list);
void stringll_push_front(StringLL* list, char* val);
char* stringll_pop_front(StringLL* list);
void stringll_print(const StringLL* list);
StringLL* stringll_clone(const StringLL* list);
void stringll_free(StringLL* list);


#endif //CHUFF_STRINGLL_H
