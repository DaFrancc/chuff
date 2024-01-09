//
// Created by dafrancc on 1/8/24.
//

#include <string.h>

#include "../include/StringBuilder.h"

StringBuilder* stringbuilder_make() {
    StringBuilder* sb = malloc(sizeof(StringBuilder));
    sb->con = stringll_create();
    sb->numChars = 0;

    return sb;
}
void stringbuilder_append(StringBuilder* sb, char* str) {
    sb->numChars = strlen(str);
    stringll_push_back(sb->con, str);
}

char* stringbulider_tostring(StringBuilder* sb) {
    char* result = calloc(sb->numChars + 1, sizeof(char));
    int i = 0;
    SLLNode* n = sb->con->head;

    while(n->next != NULL) {
        strcat(result, n->data);
    }

    return result;
}

void stringbuilder_free(StringBuilder* sb) {
    stringll_free(sb->con);
    free(sb);
}