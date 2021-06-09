#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Request input for Height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);

    for (int row = 1; row <= height; row++)
    {
        // Printing Space on Left Side
        for (int column = (height - row); column > 0; column--)
        {
            printf(" ");
        }

        // Printing # on Right Side
        for (int column = 1; column <= row; column++)
        {
            printf("#");

        }

        printf("\n");
    }
}