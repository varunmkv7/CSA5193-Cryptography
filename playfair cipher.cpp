#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to prepare the key (remove duplicate letters and handle 'J')
void prepareKey(char key[], char *preparedKey) {
    int keyLen = strlen(key);
    int index = 0;
    int i, j;

    // Copy the key to preparedKey
    strcpy(preparedKey, key);

    // Remove duplicate letters
    for (i = 0; i < keyLen; i++) {
        if (preparedKey[i] == ' ')
            continue;

        for (j = i + 1; j < keyLen; j++) {
            if (preparedKey[i] == preparedKey[j]) {
                preparedKey[j] = ' ';
            }
        }
    }

    // Replace 'J' with 'I'
    for (i = 0; i < keyLen; i++) {
        if (preparedKey[i] == 'J') {
            preparedKey[i] = 'I';
        }
    }
}

// Function to construct the Playfair matrix from the prepared key
void constructPlayfairMatrix(char preparedKey[], char playfairMatrix[5][5]) {
    int keyLen = strlen(preparedKey);
    int row = 0, col = 0;
    int usedLetters[26] = {0}; // Keep track of used letters

    for (int i = 0; i < keyLen; i++) {
        char letter = preparedKey[i];

        if (letter == ' ')
            continue;

        if (!usedLetters[letter - 'A']) {
            playfairMatrix[row][col] = letter;
            usedLetters[letter - 'A'] = 1;

            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    // Fill the rest of the matrix with remaining letters
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        if (letter == 'J')
            continue;

        if (!usedLetters[letter - 'A']) {
            playfairMatrix[row][col] = letter;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to find the positions of two letters in the Playfair matrix
void findPositions(char playfairMatrix[5][5], char letter, int *row, int *col) {
    for (*row = 0; *row < 5; (*row)++) {
        for (*col = 0; *col < 5; (*col)++) {
            if (playfairMatrix[*row][*col] == letter) {
                return;
            }
        }
    }
}

// Function to perform Playfair encryption
void playfairEncrypt(char playfairMatrix[5][5], char plaintext[], char ciphertext[]) {
    int len = strlen(plaintext);
    int index = 0;

    for (int i = 0; i < len; i++) {
        char a = toupper(plaintext[i]);
        char b = toupper(plaintext[i + 1]);

        if (a == 'J')
            a = 'I';
        if (b == 'J')
            b = 'I';

        if (a == b) {
            b = 'X';
            i--;
        }

        int row1, col1, row2, col2;
        findPositions(playfairMatrix, a, &row1, &col1);
        findPositions(playfairMatrix, b, &row2, &col2);

        if (col1 == col2) {
            ciphertext[index++] = playfairMatrix[(row1 + 1) % 5][col1];
            ciphertext[index++] = playfairMatrix[(row2 + 1) % 5][col2];
        } else if (row1 == row2) {
            ciphertext[index++] = playfairMatrix[row1][(col1 + 1) % 5];
            ciphertext[index++] = playfairMatrix[row2][(col2 + 1) % 5];
        } else {
            ciphertext[index++] = playfairMatrix[row1][col2];
            ciphertext[index++] = playfairMatrix[row2][col1];
        }

        i++;
    }

    ciphertext[index] = '\0';
}

int main() {
    char key[100];
    char plaintext[1000];
    char preparedKey[26];
    char playfairMatrix[5][5];
    char ciphertext[1000];

    printf("Enter the key: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);

    // Prepare the key (remove duplicates and replace 'J' with 'I')
    prepareKey(key, preparedKey);

    // Construct the Playfair matrix
    constructPlayfairMatrix(preparedKey, playfairMatrix);

    // Encrypt the plaintext
    playfairEncrypt(playfairMatrix, plaintext, ciphertext);

    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}

