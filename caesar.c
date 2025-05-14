#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void caesarWrap(char *text, int key);

#define ALPHABET_SIZE 26

int main(int argc, char *argv[])
{
    // Check the number of arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Get and check the key for non-negatives
    int key = atoi(argv[1]);
    if (key <= 0)
    {
        printf("Expected numeric and non-negative integer.\n");
        return 1;
    }
    key = key % ALPHABET_SIZE;

    // Get the text to cipher
    char *text = get_string("plaintext: ");

    // Make the cipher
    caesarWrap(text, key);
    return 0;
}

// Calculate the cipher and print the result
void caesarWrap(char *text, int key)
{
    int textSize = strlen(text);

    printf("ciphertext: ");
    for (int i = 0, c = 0; i < textSize; i++)
    {
        c = text[i];

        // If character isn't a letter
        if (!isalpha(c))
        {
            printf("%c", c);
            continue;
        }

        // Letter position + key % alphabetSize
        if (c >= 'A' && c <= 'Z')
        {
            c = ((c - 'A' + key) % ALPHABET_SIZE) + 'A';
        }
        else {
            c = ((c - 'a' + key) % ALPHABET_SIZE) + 'a';
        }
        printf("%c", c);
    }
    printf("\n");
}
