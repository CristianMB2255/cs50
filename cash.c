#include <cs50.h>
#include <stdio.h>

int get_cents();
int calculate_coins(int cents);

int main(void)
{
    // Prompt the user for cents value
    int cents = get_cents();

    // Sum and print the number of coins
    int coinsUsed = calculate_coins(cents);
    printf("%i\n", coinsUsed);

    return 0;
}

// Get the cents that are owed
int get_cents()
{
    int cents = 0;
    do
    {
        cents = get_int("Changed owed: ");
    }
    while (cents < 0);

    return cents;
}

// Calculate the number of coins that will be given
int calculate_coins(int cents)
{
    int coinsUsed = 0;
    do
    {
        // Calculate the quarters
        if (cents >= 25)
        {
            cents = cents - 25;
            coinsUsed++;
            continue;
        }

        // Calculate the dimes
        if (cents >= 10)
        {
            cents = cents - 10;
            coinsUsed++;
            continue;
        }

        // Calculate the nickels
        if (cents >= 5)
        {
            cents = cents - 5;
            coinsUsed++;
            continue;
        }

        // Calculate the pennies
        if (cents >= 1)
        {
            cents = cents - 1;
            coinsUsed++;
            continue;
        }
    }
    while (cents > 0);

    return coinsUsed;
}
