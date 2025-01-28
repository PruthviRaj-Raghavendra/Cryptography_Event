#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the modular multiplicative inverse
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Return -1 if modular inverse does not exist
}

// Function to encrypt the plaintext using Affine Cipher
void affine_encrypt(const char *plaintext, char *ciphertext, int a, int b) {
    int m = 26; // Size of the alphabet
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int x = ch - base; // Convert to 0-25
            int encrypted = (a * x + b) % m;
            ciphertext[i] = encrypted + base; // Convert back to ASCII
        } else {
            ciphertext[i] = ch; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the string
}

// Function to decrypt the ciphertext using Affine Cipher
void affine_decrypt(const char *ciphertext, char *plaintext, int a, int b) {
    int m = 26; // Size of the alphabet
    int a_inv = mod_inverse(a, m); // Calculate modular multiplicative inverse
    if (a_inv == -1) {
        printf("Modular inverse of 'a' does not exist.\n");
        return;
    }

    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int y = ch - base; // Convert to 0-25
            int decrypted = (a_inv * (y - b + m)) % m; // Decrypt formula
            plaintext[i] = decrypted + base; // Convert back to ASCII
        } else {
            plaintext[i] = ch; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[i] = '\0'; // Null-terminate the string
}

// Main function
int main() {
    char text[100], result[100];
    int a, b, choice;

    printf("Affine Cipher Implementation\n");

    // Validate keys
    do {
        printf("Enter key 'a' (must be coprime with 26): ");
        scanf("%d", &a);
        printf("Enter key 'b': ");
        scanf("%d", &b);

        if (gcd(a, 26) != 1) {
            printf("'a' must be coprime with 26. Try again.\n");
        }
    } while (gcd(a, 26) != 1);

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
            affine_encrypt(text, result, a, b);
            printf("Encrypted Text: %s\n", result);

        } else if (choice == 2) {
            printf("Enter the ciphertext: ");
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = '\0'; // Remove newline character
            affine_decrypt(text, result, a, b);
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

// Affine Cipher Implementation
// Enter key 'a' (must be coprime with 26): 5
// Enter key 'b': 8

// Choose an option:
// 1. Encrypt
// 2. Decrypt
// 3. Exit
// Enter your choice: 1
// Enter the plaintext: hello
// Encrypted Text: rclla

// Choose an option:
// 1. Encrypt
// 2. Decrypt
// 3. Exit
// Enter your choice: 2
// Enter the ciphertext: rclla
// Decrypted Text: hello

// Choose an option:
// 1. Encrypt
// 2. Decrypt
// 3. Exit
// Enter your choice: 3
// Exiting... Goodbye!