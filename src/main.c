#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../include/constants.h"
#include "../include/IOStream.h"

int throw_error() {
    errno = EINVAL;
    fprintf(stderr, "---INVALID ARGUMENTS---\nCorrect format:\ncompress {-t;-c} {input file} {output file}\nuncompress {input file} {output file}\nError code: %d\n", errno);
    return 1;
}

int bad_file(const char* filePath) {
    fprintf(stderr, "File %s doesn\'t exist\nError code: %d\n", filePath, errno);
    return 1;
}

int main(const int argc, const char *argv[]) {
    int format;

    if(argc == 5 && strcmp(argv[1], "compress") == 0) {
        if(strcmp(argv[2], "-t") == 0) {
            format = STORE_TREE;
        }
        else if(strcmp(argv[2], "-c") == 0) {
            format = STORE_COUNTS;
        }
        else {
            return throw_error();
        }

        BitInputStream* bis;

        if(!((bis = iostream_bitinputstream_make(argv[3])))) {
            return bad_file(argv[3]);
        }

        iostream_bitinputstream_free(bis);
    }
    else if(argc == 4 && strcmp(argv[1], "uncompress") == 0) {
        BitOutputStream* bos;

        if(!((bos = iostream_bitoutputstream_make(argv[3])))) {
            return bad_file(argv[3]);
        }

        iostream_bitoutputstream_free(bos);
    }
    else {
        return throw_error();
    }
}
