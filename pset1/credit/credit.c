# include <stdio.h>
# include <unistd.h>
# include <cs50.h>

int main()
{
    // Declare Number Digit and Sum of Total
    int num_digit = 0, total = 0;
 
    // Declare Variables to find First Two Digits
    int recent = 0, current = 0;
    
    // Request User's Input
    long credit = 0;
    do
    {
        credit = get_long("Number: ");
    }
    while (credit <= 0);
    
    // Calculating Credit Number from Last Digit
    while (credit > 0)
    {
        recent = current;
        
        // Take Current Digit from Last Digit
        current = credit % 10;
        
        if (num_digit % 2 == 0)
        {
            total += current;
        }
        
        else
        {
            int mul = current * 2;
            total += (mul % 10) + (mul / 10);
        }
        
        num_digit++;
        credit /= 10;        
    }
    
    
    if (total % 10 == 0)
    {
        int two_digits = (current * 10) + recent;
        
        // Americal Express
        if (num_digit == 15 && (two_digits == 34 || two_digits == 37))
        {
            printf("AMEX\n");
        }
        
        // Master Card
        else if (num_digit == 16 && (two_digits >= 51 && two_digits <= 55))
        {
            printf("MASTERCARD\n");
        }
        
        // VISA
        else if ((num_digit >= 13 && num_digit <= 16) && current == 4)
        {
            printf("VISA\n");
        }
        
        else
        {
            printf("INVALID\n");
        }
    }
    
    else 
    {
        printf("INVALID\n");
    }

}


    
    


