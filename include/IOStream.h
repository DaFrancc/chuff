#ifndef IOSTREAM_H
#define IOSTREAM_H

#include <stdio.h>

typedef struct BitInputStream {
    FILE* file;
    int buffer;
    int bitCount;
} BitInputStream;

typedef struct BitOutputStream {
    FILE* file;
    int buffer;
    int numBitsLeft;
} BitOutputStream;

BitInputStream* iostream_bitinputstream_make(const char* filePath);
void iostream_bitinputstream_free(BitInputStream* bis);
BitOutputStream* iostream_bitoutputstream_make(const char* filePath);
void iostream_bitoutputstream_free(BitOutputStream* bos);
long iostream_read_bits(BitInputStream* bis, int numBits);
int iostream_write_bits(BitOutputStream* bos, int numBits, int val);

#endif
