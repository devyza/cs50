from cs50 import get_int


def main():

    # Get Height from Standard Input
    height = 0
    while (height <= 0 or height > 8):
        height = get_int("Height: ")

    # Draw Pyramid
    for y in range(1, height + 1):
        print(" " * (height - y), end="")
        print("#" * y)


if __name__ == "__main__":
    main()