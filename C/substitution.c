#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int valid_key(char *key);
void encrypt_text(char *key, char *text);

#define ALPHABET_SIZE 26

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    // Validate the key
    char *key = (argv[1]);
    if (!valid_key(key))
        return 1;

    char *text = get_string("plaintext: ");

    // Encrypt the text using the key
    encrypt_text(key, text);

    printf("ciphertext: %s\n", text);
    return 0;
}

// Validate key
int valid_key(char *key)
{
    int length = strlen(key);
    char lettersUsed[ALPHABET_SIZE];

    // Check key length
    if (length != ALPHABET_SIZE)
    {
        printf("Key must contain 26 characters.\n");
        return 0;
    }

    // Check for non-alphabetical characters
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 0;
        }

        char charUpper = toupper(key[i]);
        lettersUsed[i] = charUpper;
        key[i] = charUpper;
    }

    // Check for repeated characters
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (lettersUsed[i] == lettersUsed[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 0;
            }
        }
    }
    return 1;
}

// Use the cipher and encrypt the text
void encrypt_text(char *key, char *text)
{
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        char c = text[i];
        if (!isalpha(c))
            continue;

        // Replace each letter using the key
        if (c >= 'A' && c <= 'Z')
            c = key[c - 'A'];
        else
            c = tolower(key[c - 'a']);

        text[i] = c;
    }
}
