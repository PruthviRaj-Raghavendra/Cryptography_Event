#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function prototypes
int extended_gcd(int a, int b, int *x, int *y);
int mod_exp(int base, int exp, int m);
void rsa_encrypt(char *message, int e, int n, int *cipher, int *length);
void rsa_decrypt(int *cipher, int d, int n, char *decrypted, int length);
int generate_keys(int *e, int *d, int *n);

// Function to implement the Extended Euclidean Algorithm
int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

// Function to calculate (a^b) % m using exponentiation by squaring
int mod_exp(int base, int exp, int m) {
    int result = 1;
    base = base % m;
    
    while (exp > 0) {
        if (exp % 2 == 1) // If exp is odd
            result = (result * base) % m;
        
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % m; // Square the base
    }
    return result;
}

// Function to encrypt a message using RSA
void rsa_encrypt(char *message, int e, int n, int *cipher, int *length) {
    int i;
    *length = strlen(message);
    for (i = 0; i < *length; i++) {
        cipher[i] = mod_exp((int)message[i], e, n); // Cast character to integer
    }
}

// Function to decrypt the encrypted message using RSA
void rsa_decrypt(int *cipher, int d, int n, char *decrypted, int length) {
    int i;
    for (i = 0; i < length; i++) {
        int decrypted_char = mod_exp(cipher[i], d, n);
        decrypted[i] = (char)decrypted_char; 
    }
    decrypted[length] = '\0'; // Null-terminate the decrypted string
}

// Function to generate RSA keys
int generate_keys(int *e, int *d, int *n) {
    // For demonstration, using small prime numbers. 
    // In practice, use much larger prime numbers.
    int p = 17, q = 11; 
    *n = p * q; 
    int phi = (p - 1) * (q - 1); 

    // Choose an arbitrary public exponent (e) 
    // Ensure e is relatively prime to phi (gcd(e, phi) = 1)
    *e = 7; 

    // Calculate private exponent (d) using Extended Euclidean Algorithm
    int x, y;
    extended_gcd(*e, phi, &x, &y);
    *d = (x % phi + phi) % phi; 

    return 0;
}

int main() {
    int e, d, n;
    char message[100], decrypted[100];
    int cipher[100];
    int length;
    int choice;

    // Generate RSA keys
    generate_keys(&e, &d, &n);

    printf("Public key (e, n): (%d, %d)\n", e, n);
    printf("Private key (d, n): (%d, %d)\n", d, n);

    // Menu loop for encryption and decryption
    while (1) {
        printf("\nSelect an option:\n");
        printf("1. Encrypt message\n");
        printf("2. Decrypt message\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Encrypt the message
            printf("Enter a message to encrypt: ");
            scanf("%s", message);
            rsa_encrypt(message, e, n, cipher, &length);

            // Print the encrypted message
            printf("Encrypted message (cipher text): ");
            for (int i = 0; i < length; i++) {
                printf("%d ", cipher[i]);
            }
            printf("\n");
        }
        else if (choice == 2) {
            if (length > 0) { // Ensure encryption was performed before decryption
                rsa_decrypt(cipher, d, n, decrypted, length);
                printf("Decrypted message: %s\n", decrypted);
            } else {
                printf("No encrypted message found. Please encrypt a message first.\n");
            }
        }
        else if (choice == 3) {
            break;  // Exit the program
        } else {
            printf("Invalid choice! Please select 1, 2, or 3.\n");
        }
    }

    return 0;
}



// Output

// Public key (e, n): (7, 187)
// Private key (d, n): (23, 187)

// Select an option:
// 1. Encrypt message
// 2. Decrypt message
// 3. Exit
// Enter choice: 1
// Enter a message to encrypt: HI
// Encrypted message (cipher text): 30 61 

// Select an option:
// 1. Encrypt message
// 2. Decrypt message
// 3. Exit
// Enter choice: 2
// Decrypted message: HI

// Select an option:
// 1. Encrypt message
// 2. Decrypt message
// 3. Exit
// Enter choice: 3