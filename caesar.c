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

    // Verify the key for valid input
    int key = atoi(argv[1]);
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Expected numeric and non-negative integer.\n");
            return 1;
        }
    }
    key = key % ALPHABET_SIZE;

    // Get the text to cipher
    char *text = get_string("plaintext: ");

    // Make the cipher
    caesarWrap(text, key);
    printf("ciphertext: %s\n", text);
    return 0;
}

// Calculate the cipher
void caesarWrap(char *text, int key)
{
    int textSize = strlen(text);

    for (int i = 0, c = 0; i < textSize; i++)
    {
        c = text[i];

        // If character isn't a letter
        if (!isalpha(c))
            continue;

        // Letter position + key % alphabetSize
        if (c >= 'A' && c <= 'Z')
        {
            c = ((c - 'A' + key) % ALPHABET_SIZE);
            c += 'A';
        }
        else
        {
            c = ((c - 'a' + key) % ALPHABET_SIZE);
            c += 'a';
        }

        text[i] = c;
    }
}
