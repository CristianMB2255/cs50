#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_sum(char *word);

// Global variables
const int points[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // Inputs
    char *firstWord = get_string("Input the first player word: ");
    char *secondWord = get_string("Input the second player word: ");

    // Calculations
    int firstSum = get_sum(firstWord);
    int secondSum = get_sum(secondWord);

    // Conditionals
    if (firstSum > secondSum)
        printf("Player 1 wins!\n");
    else if (secondSum > firstSum)
        printf("Player 2 wins!\n");
    else
        printf("Tie!\n");
}

// Make the sums
int get_sum(char *word)
{
    int sum = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        char character = toupper(word[i]);
        if (!isalpha(character))
            continue;

        sum += points[character - 'A'];
    }
    return sum;
}
