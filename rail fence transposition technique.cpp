#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform Rail Fence Cipher encryption
void railFenceEncrypt(char plaintext[], int rails, char ciphertext[]) {
    int textLength = strlen(plaintext);
    int gap = (rails - 1) * 2;

    int index = 0;
    for (int row = 0; row < rails; row++) {
        int step1 = row * 2;
        int step2 = gap - step1;

        int j = row;
        while (j < textLength) {
            ciphertext[index++] = plaintext[j];
            if (step1 > 0 && step2 > 0 && j + step1 < textLength) {
                j += step1;
                ciphertext[index++] = plaintext[j];
            }
            j += step2;
        }
    }
    ciphertext[index] = '\0';
}

// Function to perform Rail Fence Cipher decryption
void railFenceDecrypt(char ciphertext[], int rails, char plaintext[]) {
    int textLength = strlen(ciphertext);
    int gap = (rails - 1) * 2;
    int totalCharsInRail = (textLength / gap) + 1;

    int index = 0;
    for (int row = 0; row < totalCharsInRail; row++) {
        int step1 = row * 2;
        int step2 = gap - step1;

        int j = row;
        while (j < textLength) {
            plaintext[j] = ciphertext[index++];
            if (step1 > 0 && step2 > 0 && j + step1 < textLength) {
                j += step1;
                plaintext[j] = ciphertext[index++];
            }
            j += step2;
        }
    }
    plaintext[textLength] = '\0';
}

int main() {
    char text[1000];
    char ciphertext[1000];
    char decryptedText[1000];
    int rails;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the number of rails: ");
    scanf("%d", &rails);

    // Remove the newline character from the text
    if (text[strlen(text) - 1] == '\n') {
        text[strlen(text) - 1] = '\0';
    }

    // Encrypt the text using the Rail Fence Cipher
    railFenceEncrypt(text, rails, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    // Decrypt the ciphertext using the Rail Fence Cipher
    railFenceDecrypt(ciphertext, rails, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}

