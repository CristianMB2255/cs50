#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_words(char *text);
float count_letters(char *text, int words);
float count_sentences(char *text, int words);
int coleman_index(float letters, float sentences);

int main(void)
{
    // Get text
    char *text = get_string("Text: ");

    // Calculate text metrics
    int words = count_words(text);
    float letters = count_letters(text, words);
    float sentences = count_sentences(text, words);

    // Coleman-Liau index
    int level = coleman_index(letters, sentences);

    // Print level
    if (level < 1)
        printf("Before Grade 1\n");
    else if (level > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", level);

    return 0;
}

// Calculate the number of words
int count_words(char *text)
{
    int wordCount = 1;
    char previous = ' ';
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {

        // Check if character is a space
        char c = text[i];
        if (c == ' ' && previous != ' ')
            wordCount++;

        // Store last character for next iteration
        previous = c;
    }
    return wordCount;
}

// Count the number of letters per 100 words
float count_letters(char *text, int words)
{
    int lettersCount = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {

        // Check if char is in alphabet
        if (isalpha(text[i]))
            lettersCount++;
    }

    // Return the average per 100 words
    return ((float) lettersCount / words) * 100;
}

// Count the number of sentences per 100 words
float count_sentences(char *text, int words)
{
    char punctuations[] = ".?!";
    int length = strlen(text);
    char previous;
    int sentencesCount = 0;

    for (int i = 0; i < length; i++)
    {

        // Check if char is a punctuation
        char c = text[i];
        if (strchr(punctuations, c) && !strchr(punctuations, previous))
            sentencesCount++;

        // Store last character for next iteration
        previous = c;
    }

    // Return the average per 100 words
    return ((float) sentencesCount / words) * 100;
}

// Calculate the Coleman-Liau index
int coleman_index(float letters, float sentences)
{
    // Index = 0.0588 * L - 0.296 * S - 15.8
    float level = (0.0588 * letters) - (0.296 * sentences) - 15.8;

    return (int) round(level);
}
