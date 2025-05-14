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
    // Prompt the user for the text
    char *text;
    do
    {
        text = get_string("Text: ");
    }
    while (text[0] == '\0');

    // Calculate metrics
    int words = count_words(text);
    float letters = count_letters(text, words);
    float sentences = count_sentences(text, words);

    // Coleman-Liau index
    int level = coleman_index(letters, sentences);

    if (level < 1)
        printf("Before Grade 1\n");
    else if (level > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", level);

    return 0;
}

// Count the number of words the text has
int count_words(char *text)
{
    int length = strlen(text);
    int count_words = 1;
    int previous = 0;

    // Iterate through every char and check if its a space
    for (int i = 0; i < length; i++)
    {
        char c = text[i];
        if (c == ' ' && previous != 1)
        {
            count_words++;
            previous = 1;
        }
        previous = 0;
    }
    return count_words;
}

// Count the number of letters per 100 words
float count_letters(char *text, int words)
{
    int sum = 0;
    int length = strlen(text);

    // Check if char is in alphabet
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
            sum++;
    }

    return ((float) sum / words) * 100;
}

// Count the number of sentences per 100 words
float count_sentences(char *text, int words)
{
    char punctuations[] = {'.', '?', '!'};
    int previous = 0;
    int length = strlen(text);
    int sentences = 0;
    int sizeArray = sizeof(punctuations) / sizeof(punctuations[0]);

    for (int i = 0; i < length; i++)
    {
        char c = text[i];

        // Check if char is a punctuation
        for (int j = 0; j < sizeArray; j++)
        {
            if (c == punctuations[j] && previous != 1)
            {
                sentences++;
                previous = 1;
                break;
            }
            previous = 0;
        }
    }

    return ((float) sentences / words) * 100;
}

// Calculate the Coleman-Liau index
int coleman_index(float letters, float sentences)
{
    // index = 0.0588 * L - 0.296 * S - 15.8
    float level = (0.0588 * letters) - (0.296 * sentences) - 15.8;
    return (int) round(level);
}
