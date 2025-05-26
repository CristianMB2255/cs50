// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int HASH_LENGTH = 50000;
int sizeNodes = 0;

// Hash table
node *table[HASH_LENGTH];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lowerWord[HASH_LENGTH + 1];

    // Lowercase word
    int i = 0;
    for (i = 0; word[i] != '\0'; i++)
    {
        lowerWord[i] = tolower(word[i]);
    }
    lowerWord[i] = '\0';

    int index = hash(lowerWord);

    // Search nodes
    node *currentNode = table[index];
    while (currentNode != NULL)
    {
        // Found
        if (strcmp(lowerWord, currentNode->word) == 0)
            return true;

        // Next node
        currentNode = currentNode->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    int length = strlen(word);
    char c;

    // Loop through characters
    for (int i = 0; i < length; i++)
    {
        // Calculate hash
        c = tolower(word[i]);
        sum += (c * c) * i;
        sum = sum % HASH_LENGTH;
    }

    // Return hash value
    return sum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Failed to open %s.\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

    // Loop through words
    while (fscanf(dict, "%s", word) == 1)
    {
        // Get bucket index
        int index = hash(word);

        // Initialize node
        node *nextNode = malloc(sizeof(node));
        if (nextNode == NULL)
        {
            printf("Error while allocating memory.\n");
            fclose(dict);
            return false;
        }

        // Populating node
        strcpy(nextNode->word, word);
        nextNode->next = table[index];
        table[index] = nextNode;

        // Update nodes count
        sizeNodes++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sizeNodes;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < HASH_LENGTH; i++)
    {
        // Point to first node
        node *ptr = table[i];

        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        table[i] = NULL;
    }
    return true;
}
