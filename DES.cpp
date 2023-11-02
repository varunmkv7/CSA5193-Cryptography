#include <stdio.h>
#include <stdint.h>
#include <string.h>
static int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
                   60, 52, 44, 36, 28, 20, 12, 4,
                   62, 54, 46, 38, 30, 22, 14, 6,
                   64, 56, 48, 40, 32, 24, 16, 8,
                   57, 49, 41, 33, 25, 17, 9, 1,
                   59, 51, 43, 35, 27, 19, 11, 3,
                   61, 53, 45, 37, 29, 21, 13, 5,
                   63, 55, 47, 39, 31, 23, 15, 7};

static uint64_t key = 0x133457799BBCDFF1;
void desRound(uint32_t *left, uint32_t *right, uint32_t subkey) {
    uint32_t temp = *right;
    *right = *left ^ (temp & subkey);
    *left = temp;
}
uint64_t initialPermutation(uint64_t data) {
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        int bit = (data >> (64 - IP[i])) & 1;
        result |= ((uint64_t)bit << (63 - i));
    }
    return result;
}
void desEncrypt(uint64_t plaintext, uint64_t *ciphertext) {
    uint64_t initialPermutated = initialPermutation(plaintext);
    uint32_t left = (uint32_t)(initialPermutated >> 32);
    uint32_t right = (uint32_t)initialPermutated;
    
    for (int round = 0; round < 16; round++) {
        uint32_t subkey = (uint32_t)(key >> 28); 
        desRound(&left, &right, subkey);
        key = (key << 1) | (key >> 27);
    }
    
    
    uint64_t finalPermutated = ((uint64_t)right << 32) | left;
    *ciphertext = finalPermutated;
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t ciphertext;
    
    desEncrypt(plaintext, &ciphertext);
    
    printf("Plaintext:  0x%016llx\n", plaintext);
    printf("Ciphertext: 0x%016llx\n", ciphertext);
    
    return 0;
}
