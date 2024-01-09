//
// Created by dafrancc on 1/6/24.
//

#ifndef CHUFF_HUFFHEADER_H
#define CHUFF_HUFFHEADER_H

#include "HuffTree.h"
#include "IOStream.h"

typedef struct HuffHeader {
    char* buffer;
    int format;
    int frequencies[256];
} HuffHeader;

HuffHeader* huffheader_make(HuffTree* hTree, int format);
char* huffheader_create_header(HuffHeader* header);
int huffheader_write_header(HuffHeader* header, BitOutputStream* bos);
void huffheader_free(HuffHeader* header);

#endif //CHUFF_HUFFHEADER_H
