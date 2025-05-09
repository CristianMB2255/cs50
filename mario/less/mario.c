#include <cs50.h>
#include <stdio.h>

#define INVISIBLE " "
#define BLOCK "#"

int get_height();
void make_pyramid(int height);

int main(void)
{
    // Prompt the user for the pyramid's height
    int height = get_height();

    // Print a pyramid of that height
    make_pyramid(height);
}

// Get the height of the pyramid
int get_height()
{
    int height = 0;
    do
    {
        height = get_int("How many layers do you want your pyramid to have?\n");
    }
    while (height <= 0);

    return height;
}

// Print the pyramid
void make_pyramid(int height)
{
    for (int i = 1; i <= height; i++)
    {
        // Get the count to the invisible characters
        int inv_count = height - i;

        // Print the invisible characters
        for (int j = 0; j < inv_count; j++)
        {
            printf(INVISIBLE);
        }

        // Print the blocks
        for (int k = 0; k < i; k++)
        {
            printf(BLOCK);
        }
        // Break the line
        printf("\n");
    }
}
