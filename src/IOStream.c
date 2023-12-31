#include <stdio.h>
#include <stdlib.h>

#include "../include/IOStream.h"

#define BITS_PER_BYTE 8


static const int bmask[] = {
    0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff,
    0x1ff,0x3ff,0x7ff,0xfff,0x1fff,0x3fff,0x7fff,0xffff,
    0x1ffff,0x3ffff,0x7ffff,0xfffff,0x1fffff,0x3fffff,
    0x7fffff,0xffffff,0x1ffffff,0x3ffffff,0x7ffffff,
    0xfffffff,0x1fffffff,0x3fffffff,0x7fffffff,0xffffffff
};

BitInputStream* iostream_bitinputstream_make(const char* filePath) {
    FILE* file;

    if(!((file = fopen(filePath, "r")))) {
        return NULL;
    }

    BitInputStream* bis = malloc(sizeof(BitInputStream));

    bis->file = file;
    bis->buffer = 0;
    bis->bitCount = 0;

    return bis;
}

void iostream_bitinputstream_free(BitInputStream* bis) {
    fclose(bis->file);
    free(bis);
}

BitOutputStream* iostream_bitoutputstream_make(const char* filePath) {
    FILE* file;

    if(!((file = fopen(filePath, "w")))) {
        return NULL;
    }

    BitOutputStream* bos = malloc(sizeof(BitOutputStream));

    bos->file = file;
    bos->buffer = 0;
    bos->numBitsLeft = 0;

    return bos;
}

void iostream_bitoutputstream_free(BitOutputStream* bos) {
    iostream_write_bits(bos, bos->numBitsLeft, 0);
    fclose(bos->file);
    free(bos);
}

long iostream_read_bits(BitInputStream* bis, int numBits) {

    int res = 0;

    while(numBits > bis->bitCount) {
        res |= (bis->buffer << (numBits - bis->bitCount));
        numBits -= bis->bitCount;

        if((bis->buffer = fgetc(bis->file)) == EOF) {
            return -1;
        }
        bis->bitCount = BITS_PER_BYTE;
    }

    if(numBits > 0) {
        res |= bis->buffer >> (bis->bitCount - numBits);
        bis->buffer &= bmask[bis->bitCount - numBits];
        bis->bitCount -= numBits;
    }

    return res;
}



int iostream_write_bits(BitOutputStream* bos, int numBits, int val) {
    val &= bmask[numBits];

    int bitsWritten = 0;

    while(numBits >= bos->numBitsLeft) {
        bos->buffer = (bos->buffer << bos->numBitsLeft)
            | (val >> (numBits - bos->numBitsLeft));
        if((bitsWritten = fprintf(bos->file, "%d", bos->buffer)) < 0) {
            return -1;
        }

        val &= bmask[numBits - bos->numBitsLeft];
        numBits -= bos->numBitsLeft;
        bos->numBitsLeft = BITS_PER_BYTE;
        bos->buffer = 0;
    }

    if(numBits > 0) {
        bos->buffer = (bos->buffer <<numBits) | val;
        bos->numBitsLeft -= numBits;
    }

    return bitsWritten;
}
