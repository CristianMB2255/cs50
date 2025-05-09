#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long get_credit_number();
int get_card_info(char *numberStr, int length, char **cardType);
int validate_card(char *numberStr, int length);

int main(void)
{
    int return_value = 1;
    char numberStr[17];
    char *cardType = NULL;

    // Get the credit card number
    long number = get_credit_number();
    sprintf(numberStr, "%ld", number);

    // Get the length of the number
    int length = strlen(numberStr);

    // Get the type of the card and validate it
    if (get_card_info(numberStr, length, &cardType) == 0 || validate_card(numberStr, length) == 1)
    {
        printf("INVALID\n");
        return 0;
    }

    // If correct, print the card type
    printf("%s\n", cardType);
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
int get_card_info(char *numberStr, int length, char **cardType)
{
    // AMEX: 15; 34, 37
    // Master: 16; 51, 52, ..., 55
    // VISA: 13 or 16; 4

    if (length == 15 && numberStr[0] == '3' && strchr("47", numberStr[1]))
    {
        *cardType = "AMEX";
        return 1;
    }
    if ((length == 13 || length == 16) && numberStr[0] == '4')
    {
        *cardType = "VISA";
        return 1;
    }
    if (length == 16 && numberStr[0] == '5' && strchr("12345", numberStr[1]))
    {
        *cardType = "MASTERCARD";
        return 1;
    }

    // Return if the card isn't in a valid format
    return 0;
}

// Validate the credit card digits
int validate_card(char *numberStr, int length)
{
    int sum = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        int digit = numberStr[i] - '0';
        if ((length - i) % 2 == 0)
            digit = digit * 2;

        if (digit > 9)
            sum += digit - 9;
        else
            sum += digit;
    }
    return sum % 10 != 0;
}
