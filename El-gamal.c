#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to compute modular exponentiation (base^exp % mod)
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to compute modular inverse using Extended Euclidean Algorithm
long long modInverse(long long a, long long p) {
    long long t = 0;
    long long newT = 1;
    long long r = p;
    long long newR = a;
    long long quotient, temp;

    while (newR != 0) {
        quotient = r / newR;
        temp = t;
        t = newT;
        newT = temp - quotient * newT;
        temp = r;
        r = newR;
        newR = temp - quotient * newR;
    }

    if (r > 1) {
        return -1;  // Inverse doesn't exist
    }

    if (t < 0) {
        t = t + p;
    }
    return t;
}

// Function to encrypt a message (either text or number)
void encryptMessage(long long p, long long g, long long y, long long m, long long *c1, long long *c2) {
    long long r = rand() % (p - 2) + 1;  // Random r such that 1 <= r <= p-1
    *c1 = modExp(g, r, p);  // c1 = g^r % p
    *c2 = (m * modExp(y, r, p)) % p;  // c2 = m * y^r % p
}

// Function to decrypt the message
long long decryptMessage(long long p, long long c1, long long c2, long long x) {
    long long inverseC1 = modExp(c1, p - 1 - x, p);
    long long m = (c2 * inverseC1) % p;  // m = c2 * (c1^x)^(-1) % p
    return m;
}

// Function to encrypt a string (convert each character to its ASCII value)
void encryptString(char* message, long long p, long long g, long long y, long long *encryptedMessageC1, long long *encryptedMessageC2) {
    int i = 0;
    while (message[i] != '\0') {
        long long m = (long long)message[i];
        encryptMessage(p, g, y, m, &encryptedMessageC1[i], &encryptedMessageC2[i]);
        i++;
    }
    encryptedMessageC1[i] = -1;  // End of message indicator
    encryptedMessageC2[i] = -1;
}

// Function to decrypt a string (convert each encrypted ASCII value back to character)
void decryptString(long long *encryptedMessageC1, long long *encryptedMessageC2, long long p, long long x, char *decryptedMessage) {
    int i = 0;
    while (encryptedMessageC1[i] != -1) {
        long long decryptedValue = decryptMessage(p, encryptedMessageC1[i], encryptedMessageC2[i], x);
        decryptedMessage[i] = (char)decryptedValue;
        i++;
    }
    decryptedMessage[i] = '\0';  // Null-terminate the decrypted string
}

int main() {
    long long p, g, y, x, c1, c2;
    char message[100], decryptedMessage[100];
    long long encryptedMessageC1[100], encryptedMessageC2[100];

    // Step 1: Enter prime number p
    printf("Enter a large prime number p: ");
    scanf("%lld", &p);

    // Step 2: Select a primitive root g modulo p
    printf("Enter a primitive root g modulo p: ");
    scanf("%lld", &g);

    // Step 3: Choose private key x and calculate y
    printf("Enter private key x: ");
    scanf("%lld", &x);
    y = modExp(g, x, p);  // y = g^x % p

    // Step 4: Display public key (p, g, y)
    printf("Public Key: (p = %lld, g = %lld, y = %lld)\n", p, g, y);

    // Step 5: Enter message to encrypt
    printf("Enter the message to encrypt (string or number): ");
    scanf(" %[^\n]%*c", message);  // Accept a string message (including spaces)

    // Check if the input is numeric (an integer)
    long long m;
    if (sscanf(message, "%lld", &m) == 1) {
        // If input is a number, encrypt and decrypt it directly
        encryptMessage(p, g, y, m, &c1, &c2);
        long long decryptedMessageNum = decryptMessage(p, c1, c2, x);
        printf("\nEncrypted Message: (c1 = %lld, c2 = %lld)\n", c1, c2);
        printf("Decrypted Message: %lld\n", decryptedMessageNum);
    } else {
        // If input is a string, process each character
        encryptString(message, p, g, y, encryptedMessageC1, encryptedMessageC2);
        decryptString(encryptedMessageC1, encryptedMessageC2, p, x, decryptedMessage);
        printf("\nEncrypted Message: ");
        for (int i = 0; encryptedMessageC1[i] != -1; i++) {
            printf("(c1 = %lld, c2 = %lld) ", encryptedMessageC1[i], encryptedMessageC2[i]);
        }
        printf("\nDecrypted Message: %s\n", decryptedMessage);  // Print the decrypted string
    }

    return 0;
}
/* SAMPLE OUTPUT
Enter a large prime number p: 7841
Enter a primitive root g modulo p: 2
Enter private key x: 35
Public Key: (p = 7841, g = 2, y = 5908)
Enter the message to encrypt (string or number): HARSHITHA
Encrypted Message: (c1 = 666, c2 = 1750) (c1 = 5924, c2 = 3218) (c1 = 1393, c2 = 5023) (c1 = 1552, c2 = 4810) (c1 = 3717, c2 = 1426) (c1 = 5177, c2 = 994) (c1 = 3434, c2 = 122) (c1 = 7682, c2 = 6091) (c1 = 3960, c2 = 5096) 
Decrypted Message: HARSHITHA

SAMPLE OUTPIT 2
Enter a large prime number p: 7919
Enter a primitive root g modulo p: 3
Enter private key x: 45
Public Key: (p = 7919, g = 3, y = 1502)
Enter the message to encrypt (string or number): cryptography
Encrypted Message: (c1 = 4093, c2 = 6858) (c1 = 6339, c2 = 2895) (c1 = 7832, c2 = 5565) (c1 = 6705, c2 = 1142) (c1 = 1593, c2 = 6590) (c1 = 383, c2 = 3186) (c1 = 7372, c2 = 2246) (c1 = 182, c2 = 2979) (c1 = 4697, c2 = 7134) (c1 = 4566, c2 = 3113) (c1 = 7242, c2 = 3801) (c1 = 2163, c2 = 2879) 
Decrypted Message: cryptography
 */
