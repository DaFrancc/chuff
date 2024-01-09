//
// Created by dafrancc on 1/8/24.
//

#ifndef CHUFF_STRINGBUILDER_H
#define CHUFF_STRINGBUILDER_H

#include <stdlib.h>
#include "StringLL.h"

typedef struct StringBuilder {
    StringLL* con;
    size_t numChars;
} StringBuilder;

StringBuilder* stringbuilder_make();
void stringbuilder_append(StringBuilder* sb, char* str);
char* stringbulider_tostring(StringBuilder* sb);
void stringbuilder_free(StringBuilder* sb);

#endif //CHUFF_STRINGBUILDER_H
