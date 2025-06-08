from cs50 import get_int

# Get the type of the credit card


def get_card_type(number, numberLength):

    # AMEX: 15 length; starts with: 34, 37
    # Master: 16 length; starts with: 51, 52, ..., 55
    # VISA: 13 or 16 length; starts with: 4

    if numberLength == 15 and number[0] == '3' and number[1] in ["4", "7"]:
        return "AMEX"

    elif (numberLength == 13 or numberLength == 16) and number[0] == '4':
        return "VISA"

    elif numberLength == 16 and number[0] == '5' and number[1] in ['1', '2', '3', '4', '5']:
        return "MASTERCARD"

    else:
        return "INVALID"

# Validate the credit card digits


def luhn_checksum(number, numberLength):

    sum = 0

    # Iterate through number
    for i in range(numberLength):
        char = int(number[i])

        # If even
        # Double the digit and sum the product's digits
        if (numberLength - i) % 2 == 0:
            char = char * 2

        if char > 9:
            sum += char - 9

        # If odd
        # Sum the digit
        else:
            sum += char

    return sum


# Get the credit card number & length
number = 0

while number <= 0:
    number = get_int("The the credit card number: ")

number = str(number)
numberLength = len(number)

# Get card info
cardType = get_card_type(number, numberLength)

if (cardType == "INVALID"):
    print("INVALID")
    exit()

# Validate the card w/ Hans Peter Luhn algorithm
sum = luhn_checksum(number, numberLength)

# Print the card type or invalid
if sum % 10 == 0:
    print(cardType)

else:
    print("INVALID")
