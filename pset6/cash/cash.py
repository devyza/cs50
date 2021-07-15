from cs50 import get_float

coins = [25, 10, 5, 1]


def main():

    # Get user's money from standard input
    owned = 0.0
    while (owned <= 0):
        owned = get_float("Change Owned: ")

    # Convert money into cents
    total = owned * 100
    count = 0

    # Trying a new method by using array and while loop
    for i in coins:
        # Minus and count until
        while i <= total:
            total -= i
            count += 1

    # Dispaly total coin as standard output
    print(count)


if __name__ == "__main__":
    main()