#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int gcd;
    int x;
    int y;
} EuclidResult;

EuclidResult extendedEuclidean(int a, int b) {
    if (b == 0) {
        EuclidResult result = {a, 1, 0};
        return result;
    }

    EuclidResult prev = extendedEuclidean(b, a % b);
    EuclidResult current = {
        prev.gcd,
        prev.y,
        prev.x - (a / b) * prev.y
    };

    return current;
}

int modInverse(int a, int m) {
    EuclidResult result = extendedEuclidean(a, m);
    
    if (result.gcd != 1) {
        return -1;
    } else {
        return (result.x % m + m) % m;
    }
}

int main() {
    int a, m;

    printf("Enter two positive integers:\n");
    printf("First integer (a): ");
    if (scanf("%d", &a) != 1 || a <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    printf("Second integer (m): ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    EuclidResult result = extendedEuclidean(a, m);

    printf("\nResults:\n");
    printf("GCD(%d, %d) = %d\n", a, m, result.gcd);

    int inverse = modInverse(a, m);
    if (inverse != -1) {
        printf("Modular inverse of %d modulo %d is: %d\n", a, m, inverse);
        printf("Verification: (%d * %d) mod %d = %d\n", a, inverse, m, (a * inverse) % m);
    } else {
        printf("Modular inverse does not exist as %d and %d are not coprime.\n", a, m);
    }

    return 0;
}
/* sample output-1
  First integer (a): 57
Second integer (m): 3

Results:
GCD(57, 3) = 3
Modular inverse does not exist as 57 and 3 are not coprime.
 */
/* sample output-2
Enter two positive integers:
First integer (a): 19
Second integer (m): 5

Results:
GCD(19, 5) = 1
Modular inverse of 19 modulo 5 is: 4
Verification: (19 * 4) mod 5 = 1
*/
