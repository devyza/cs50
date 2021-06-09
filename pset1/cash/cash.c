#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int owned;  
    do
    {
        // Request User's Input
        float dollar = get_float("Change Owned: ");
        // Convert into Coin
        owned = round(dollar * 100);
    }
    while (owned <= 0);
    
    int quarter = owned / 25;
    int dimes = (owned % 25) / 10;
    int nickel = ((owned % 25) % 10) / 5;
    int pennie = ((owned % 25) % 10) %  5;
    
    printf("%d", quarter + dimes + nickel + pennie);
}

