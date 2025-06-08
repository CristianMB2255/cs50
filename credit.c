#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long get_credit_number();
void get_card_type(char *number, int numberLength, char **cardType);
int luhn_checksum(char *number, int numberLength);

int main(void)
{
    char number[17];
    char *cardType = NULL;

    // Get the credit card number & length
    sprintf(number, "%ld", get_credit_number());
    int numberLength = strlen(number);

    // Get card info
    get_card_type(number, numberLength, &cardType);

    if (strcmp(cardType, "INVALID") == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Validate the card w/ Hans Peter Luhn algorithm
    int sum = luhn_checksum(number, numberLength);

    // Print the card type or invalid
    if (sum % 10 == 0)
    {
        printf("%s\n", cardType);
    }

    else
    {
        printf("INVALID\n");
    }
    return 0;
}

// Get the number of the credit card
long get_credit_number()
{
    long number = 0;
    do
    {
        number = get_long("Type the credit card number: ");
    }
    while (number <= 0);

    return number;
}

// Get the type of the credit card
void get_card_type(char *number, int numberLength, char **cardType)
{
    // AMEX: 15 length; starts with: 34, 37
    // Master: 16 length; starts with: 51, 52, ..., 55
    // VISA: 13 or 16 length; starts with: 4

    if (numberLength == 15 && number[0] == '3' && strchr("47", number[1]))
        *cardType = "AMEX";

    else if ((numberLength == 13 || numberLength == 16) && number[0] == '4')
        *cardType = "VISA";

    else if (numberLength == 16 && number[0] == '5' && strchr("12345", number[1]))
        *cardType = "MASTERCARD";

    else
        *cardType = "INVALID";
}

// Validate the credit card digits
int luhn_checksum(char *number, int numberLength)
{
    int sum = 0;

    // Iterate through number
    for (int i = 0; i < numberLength; i++)
    {
        int digit = number[i] - '0';

        // If even
        // Double the digit and sum the product's digits
        if ((numberLength - i) % 2 == 0)
            digit = digit * 2;

        if (digit > 9)
            sum += digit - 9;

        // If odd
        // Sum the digit
        else
            sum += digit;
    }
    return sum;
}
