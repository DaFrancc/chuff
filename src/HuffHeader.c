//
// Created by dafrancc on 1/6/24.
//

#include <string.h>

#include "../include/HuffHeader.h"
#include "../include/constants.h"
#include "../include/StringBuilder.h"

static void make_counts_format(int freqs[256], TreeNode* n) {
    if(n != NULL) {
        if(treenode_isleaf(n) && n->value != PSEUDO_EOF) {
            freqs[n->value] = n->frequency;
        }
        make_counts_format(freqs, n->left);
        make_counts_format(freqs, n->right);
    }
}

static char* longToBinaryString(long num) {
    const int bits = sizeof(long) * 8; // Number of bits in a long
    char* binaryStr = (char*)malloc(bits + 1); // Allocate memory for the binary string

    if (binaryStr == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    binaryStr[bits] = '\0'; // Null-terminate the string

    for (int i = bits - 1; i >= 0; i--) {
        binaryStr[i] = (num & 1) ? '1' : '0'; // Extract the least significant bit
        num >>= 1; // Shift number to the right by 1 bit
    }

    return binaryStr;
}

static char* get_full_binary(const int n, const int desiredLength) {
    StringBuilder* result = stringbuilder_make();
    char* original = longToBinaryString(n);
    size_t origSize = strlen(original);

    for(int i = 0; i < desiredLength - origSize; ++i) {
        stringbuilder_append(result, "0");
    }

    stringbuilder_append(result, original);

    return stringbulider_tostring(result);
}

static void make_tree_format(StringBuilder* sb, TreeNode* n) {
    if(n != NULL) {
        if(!treenode_isleaf(n)) {
            stringbuilder_append(sb, "0");
        }
        else {
            stringbuilder_append(sb, "1");
            stringbuilder_append(sb, get_full_binary(n->value, 9));
        }
        make_tree_format(sb, n->left);
        make_tree_format(sb, n->right);
    }
}

HuffHeader* huffheader_make(HuffTree* hTree, int format) {
    HuffHeader* header = malloc(sizeof(HuffHeader));

    StringBuilder* sb = stringbuilder_make();
    header->format = format;

    switch(format) {
        case STORE_COUNTS:
            make_counts_format(header->frequencies, hTree->root);
            break;
        case STORE_TREE:
            make_tree_format(sb, hTree->root);
            header->buffer = stringbulider_tostring(sb);
            break;
        default:
            exit(1);
    }

    return header;
}


void huffheader_free(HuffHeader* header) {
    free(header->buffer);
    free(header);
}

char* huffheader_create_header(HuffHeader* header) {
    switch(header->format) {
        case STORE_COUNTS:
            StringBuilder* sb = stringbuilder_make();
            const size_t length = sizeof(header->frequencies) / sizeof(header->frequencies[0]);
            for(int i = 0; i < length; ++i) {
                stringbuilder_append(sb, get_full_binary(header->frequencies[i], 32));
            }
            header->buffer = stringbulider_tostring(sb);
            return header->buffer;
        case STORE_TREE:
            char* size = get_full_binary(strlen(header->buffer), 32);
            char* temp = header->buffer;
            header->buffer = malloc(sizeof(header->buffer) + sizeof(size) - 1); // Subtracting 1 because there are 2 null terminators and we only need one

            sprintf(header->buffer, "%s%s", size, temp);
            return header->buffer;
        default:
            exit(1);
    }
}
int huffheader_write_header(HuffHeader* header, BitOutputStream* bos) {
    const int ZERO_ASCII = 48;
    char* fullHeader = huffheader_create_header(header);
    const size_t bitsWritten = strlen(fullHeader);
    for(int i = 0; i < bitsWritten; ++i) {
        iostream_write_bits(bos, 1, fullHeader[i] == ZERO_ASCII ? 0 : 1);
    }
    return bitsWritten;
}
