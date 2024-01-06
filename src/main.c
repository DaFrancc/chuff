#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../include/constants.h"
#include "../include/IOStream.h"
#include "../include/HuffTree.h"
#include "../include/HashMap.h"

int throw_error() {
    errno = EINVAL;
    fprintf(stderr, "---INVALID ARGUMENTS---\nCorrect format:\ncompress {-t;-c} {input file} {output file}\nuncompress {input file} {output file}\nError code: %d\n", errno);
    return 1;
}

int bad_file(const char* filePath) {
    fprintf(stderr, "File %s doesn\'t exist\nError code: %d\n", filePath, errno);
    return 1;
}

HuffTree* make_hufftree(BitInputStream* bis) {
    int arr[ALPH_SIZE] = {0};

    int bits = iostream_read_bits(bis, BITS_PER_WORD);

    while(bits != -1) {
        arr[bits]++;
        bits = iostream_read_bits(bis, BITS_PER_WORD);
    }

    PriorityQueue* pq = priorityqueue_make(linkedlist_create());

    for (int i = 0; i < ALPH_SIZE; ++i) {
        if(arr[i] != 0) {
            priorityqueue_enqueue(pq, treenode_make(i, arr[i]));
        }
    }

    priorityqueue_enqueue(pq, treenode_make(PSEUDO_EOF, 1));

    return hufftree_make_from_pq(pq);
}

int oSize = 0;
int cSize = 0;
HuffTree* hTree = NULL;
HashMap* valToPathMap = NULL;

void create_map(TreeNode* n, char* path) {
    if(treenode_isleaf(n)) {
        hashmap_put(valToPathMap, n->value, path);
    }
    else {
        // 3 = 1 byte for null terminator, 2 bytes for the 2 extra chars
        char* newPath = calloc(strlen(path) + 3, sizeof(char));
        sprintf(newPath, "%s%c", path, '0');
        free(path);
        create_map(n->left, newPath);
        sprintf(newPath, "%s%c", newPath, '1');
        create_map(n->right, newPath);
    }
}

void calculate_size(int format) {
    // Bits for magic number and header format
    cSize += BITS_PER_LONG * 2;

//    // Bits for header
//    cSize += new HuffHeader(hTree, format).makeHeader().length();
//
//    // Bits for file content including PSEUDO_EOF
//    for (TreeNode n : priorityQueue)
//    {
//        cSize += n.getFrequency() * valToPathMap.get(n.getValue()).length();
//        oSize += n.getFrequency() * BITS_PER_WORD;
//    }
//
//    // This is to account for the PSEUDO_EOF
//    oSize -= BITS_PER_WORD;
}

int preprocess(BitInputStream* bis, int format) {
    oSize = 0;
    cSize = 0;

    hTree = make_hufftree(bis);
    valToPathMap = hashmap_make(hTree->size);

    char* path = calloc(1, sizeof(char));

    create_map(hTree->root, path);

    calculate_size(format);
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

        int bits = preprocess(bis, format);

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
