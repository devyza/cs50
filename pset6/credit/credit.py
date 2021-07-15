import re
from cs50 import get_string


def main():

    # Get card number from user input (stdin)
    cardNumber = None
    while cardNumber == None:
        cardNumber = get_string("Number: ")

    # Check the card Number
    if (luhn_checksum(cardNumber) != 0):
        print("INVALID")
        return 1

    # Match the card pattern
    print(match(cardNumber))


# Generate Luhn's checksum by using slice notation [start:end:step]
# Reference https://railsware.com/blog/python-for-machine-learning-indexing-and-slicing-for-lists-tuples-strings-and-other-sequential-types/
def luhn_checksum(cardNumber):

    total = 0

    # Starting from the last index of the array, add number
    for i, j in cardNumber[-1:0]:

        # Sum the digits which won't multiple by 2 starting from last digit
        total += int(i)

        # Multiply every other digit by 2, starting with the number’s second-to-last digit
        j = int(j) * 2
        total += (j % 10) + (j // 10)

    return total % 10


# Match the card pattern using Regex Expression (re)
def match(cardNumber):

    # Americal Express
    if re.match(r"^3[4-7]\d{13}", cardNumber):
        return "AMEX"

    # MasterCard
    elif re.match(r"^(22)|(5[1-5])\d{14}", cardNumber):
        return "MASTERCARD"

    # VISA
    elif re.match(r"^4\d{12,15}", cardNumber):
        return "VISA"

    else:
        return "INVALID"


if __name__ == "__main__":
    main()