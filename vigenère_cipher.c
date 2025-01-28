#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt plaintext using Vigenère Cipher
void vigenere_encrypt(const char *plaintext, const char *key, char *ciphertext) {
    int key_len = strlen(key);
    int i, j = 0;

    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            char key_base = isupper(key[j % key_len]) ? 'A' : 'a';
            int shift = key[j % key_len] - key_base;
            ciphertext[i] = ((ch - base + shift) % 26) + base;
            j++; // Move to the next character in the key
        } else {
            ciphertext[i] = ch; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the string
}

// Function to decrypt ciphertext using Vigenère Cipher
void vigenere_decrypt(const char *ciphertext, const char *key, char *plaintext) {
    int key_len = strlen(key);
    int i, j = 0;

    for (i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            char key_base = isupper(key[j % key_len]) ? 'A' : 'a';
            int shift = key[j % key_len] - key_base;
            plaintext[i] = ((ch - base - shift + 26) % 26) + base;
            j++; // Move to the next character in the key
        } else {
            plaintext[i] = ch; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[i] = '\0'; // Null-terminate the string
}

// Main function
int main() {
    char text[100], result[100], key[100];
    int choice;

    printf("Vigenère Cipher Implementation\n");
    printf("Enter the key (alphabetic characters only): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    // Validate the key (only alphabetic characters allowed)
    for (int i = 0; i < strlen(key); i++) {
        if (!isalpha(key[i])) {
            printf("Key must only contain alphabetic characters. Exiting...\n");
            return 1;
        }
    }

    while (1) { // Infinite loop until the user decides to exit
        printf("\nChoose an option:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left in the buffer

        if (choice == 1) {
            printf("Enter the plaintext: ");
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = '\0'; // Remove newline character
            vigenere_encrypt(text, key, result);
            printf("Encrypted Text: %s\n", result);

        } else if (choice == 2) {
            printf("Enter the ciphertext: ");
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = '\0'; // Remove newline character
            vigenere_decrypt(text, key, result);
            printf("Decrypted Text: %s\n", result);

        } else if (choice == 3) {
            printf("Exiting... Goodbye!\n");
            break;

        } else {
            printf("Invalid choice. Please select 1, 2, or 3.\n");
        }
    }

    return 0;
}


// Output

// Vigenère Cipher Implementation
// Enter the key (alphabetic characters only): hello

// Choose an option:
// 1. Encrypt
// 2. Decrypt
// 3. Exit
// Enter your choice: 1
// Enter the plaintext: HI hello
// Encrypted Text: OM spzss

// Choose an option:
// 1. Encrypt
// 2. Decrypt
// 3. Exit
// Enter your choice: 2
// Enter the ciphertext: OM spzss
// Decrypted Text: HI hello

// Choose an option:
// 1. Encrypt
// 2. Decrypt
// 3. Exit
// Enter your choice: 3
// Exiting... Goodbye!