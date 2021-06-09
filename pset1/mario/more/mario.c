#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    do
    {
        height = get_int("Height: "); 
    }
    while (height <= 0 || height > 8);
    
    for (int row = 1; row <= height; row++)
    {
        // Drawing Blankspace
        for (int column = height - row; column > 0; column--)
        {
            printf(" ");
        }
        
        // Drawing # on the Left
        for (int column = 0; column < row; column++)
        {
            printf("#");
        }
        
        // Drawing Blankspae in the centre
        printf("  ");
        
        // Drawing # on the Right
        for (int column = 0; column < row; column++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}
