#include <stdio.h>
#include <string.h>
#include <ctype.h> 

void vigenere_encrypt(char *plaintext, char *key) {
    int key_len = strlen(key);
    for (int i = 0, j = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            plaintext[i] = ((plaintext[i] - offset + key[j % key_len] - 'A') % 26) + offset;
            j++;
        }
    }
}

void vigenere_decrypt(char *ciphertext, char *key) {
    int key_len = strlen(key);
    for (int i = 0, j = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            ciphertext[i] = ((ciphertext[i] - offset - (key[j % key_len] - 'A') + 26) % 26) + offset;
            j++;
        }
    }
}

int main() {
    char text[100], key[100];

    printf("Enter the text to encrypt (uppercase letters only): ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the key (uppercase letters only): ");
    fgets(key, sizeof(key), stdin);

    text[strcspn(text, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    printf("Original Text: %s\n", text);
    vigenere_encrypt(text, key);
    printf("Encrypted Text: %s\n", text);

    vigenere_decrypt(text, key);
    printf("Decrypted Text: %s\n", text);

    return 0;
}
/* sample output
Enter the text to encrypt (uppercase letters only): HARSHITHA
Enter the key (uppercase letters only): CRPYTOGRAPHY
Original Text: HARSHITHA
Encrypted Text: JRGQAWZYA
Decrypted Text: HARSHITHA

SAMPLE OUTPUT-2
Enter the text to encrypt (uppercase letters only): ENGINEERING
Enter the key (uppercase letters only): COMPUTER
Original Text: ENGINEERING
Encrypted Text: GBSXHXIIKBS
Decrypted Text: ENGINEERING
*/
