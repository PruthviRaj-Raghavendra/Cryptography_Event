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
    int x, y;
    int gcd = extended_gcd(a, m, &x, &y);

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


// Output 

// Number with Modular inverse

// Enter a number to find its modular inverse: 5
// Enter the modulus (m): 26
// The modular inverse of 5 mod 26 is: 21

// Number without Modular inverse

// Enter a number to find its modular inverse: 2
// Enter the modulus (m): 4
// No modular inverse exists for 2 mod 4