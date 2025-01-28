#include <stdio.h>
#include <stdlib.h>

// Function to calculate (a^b) % mod using modular exponentiation
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)  // If exp is odd
            result = (result * base) % mod;
        exp = exp >> 1;    // Divide exp by 2
        base = (base * base) % mod; // Square the base
    }
    return result;
}

int main() {
    int p, e1, e2, d, r, m, c1, c2, decrypted;

    // Input prime number p
    printf("Enter a prime number p: ");
    scanf("%d", &p);

    // Input generator e1
    printf("Enter generator e1 (must be < p): ");
    scanf("%d", &e1);

    // Input private key d
    printf("Enter private key d (must be < p): ");
    scanf("%d", &d);

    // Compute e2 = (e1^d) % p
    e2 = mod_exp(e1, d, p);
    printf("Public key e2 computed as (e1^d) mod p: %d\n", e2);

    // Input random integer r
    printf("Enter a random integer r (must be < p): ");
    scanf("%d", &r);

    // Input message m
    printf("Enter the message m (must be < p): ");
    scanf("%d", &m);

    // Encryption: Compute c1 and c2
    c1 = mod_exp(e1, r, p);  // c1 = (e1^r) % p
    c2 = (m * mod_exp(e2, r, p)) % p;  // c2 = (m * (e2^r)) % p

    printf("Ciphertext: c1 = %d, c2 = %d\n", c1, c2);

    // Decryption: Compute decrypted message m
    int s = mod_exp(c1, d, p); // s = (c1^d) % p
    int s_inv = mod_exp(s, p - 2, p); // Compute modular inverse of s using Fermat's Little Theorem
    decrypted = (c2 * s_inv) % p;

    // Ensure decrypted message is positive
    if (decrypted < 0) 
        decrypted += p;

    printf("Decrypted message: %d\n", decrypted);

    return 0;
}
