#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform Vigenère cipher encryption
void vigenereEncrypt(char text[], char key[]) {
    int textLength = strlen(text);
    int keyLength = strlen(key);

    for (int i = 0; i < textLength; i++) {
        if (isalpha(text[i])) {
            char textChar = islower(text[i]) ? 'a' : 'A';
            char keyChar = islower(key[i % keyLength]) ? 'a' : 'A';

            int shift = (key[i % keyLength] - keyChar) % 26;
            text[i] = (text[i] - textChar + shift) % 26 + textChar;
        }
    }
}

int main() {
    char plaintext[1000];
    char key[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the Vigenere key: ");
    scanf("%s", key);

    // Remove the newline character from the plaintext
    if (plaintext[strlen(plaintext) - 1] == '\n') {
        plaintext[strlen(plaintext) - 1] = '\0';
    }

    // Encrypt the plaintext using the Vigenère cipher
    vigenereEncrypt(plaintext, key);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}

