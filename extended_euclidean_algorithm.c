#include <stdio.h>

// Function to implement the Extended Euclidean Algorithm
int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a; // gcd(a, b)
    }
    int x1, y1; // Temporary variables to store results of recursive call
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

// Function to find the modular inverse
void modular_inverse(int a, int m) {
    int x, y, t1, t2;
    int gcd = extended_gcd(a, m, &x, &y);

    // Store intermediate results in t1 and t2
    t1 = x;
    t2 = y;

    printf("The GCD of %d and %d is: %d\n", a, m, gcd); // Print the GCD
    printf("Intermediate results: t1 = %d, t2 = %d\n", t1, t2); // Print t1 and t2

    if (gcd != 1) {
        printf("No modular inverse exists for %d mod %d\n", a, m);
        return;
    }

    // Ensure the result is positive
    int mod_inverse = (x % m + m) % m;
    printf("The modular inverse of %d mod %d is: %d\n", a, m, mod_inverse);
}

int main() {
    int a, m;
    
    // User input for the number and modulus
    printf("Enter a number to find its modular inverse: ");
    scanf("%d", &a);
    printf("Enter the modulus (m): ");
    scanf("%d", &m);

    // Function call to find the modular inverse
    modular_inverse(a, m);

    return 0;
}
