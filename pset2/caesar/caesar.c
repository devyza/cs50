#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool isValid(string argv);
string request_input();
string caesar(string plaintext, int position);

int main(int argc, string argv[])
{

    if (argc == 2 && isValid(argv[1]))
    {
        // To convert string ("") to int
        int k = atoi(argv[1]);

        // Get return value from request_input() function
        string plaintext = request_input();

        printf("Cipher Text: %s\n", caesar(plaintext, k));
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    return 0;

}

string request_input()
{
    string text = "\0";
    do
    {
        text = get_string("Plain Text: ");
    }
    while (strlen(text) <= 0);

    return text;
}

string caesar(string text, int k)
{
    int i = 0;

    for (int count = 0; count < strlen(text); count++)
    {
        if (isalpha(text[count]))
        {
            i = isupper(text[count]) ? 65 : 97;

            //    c = (p + k) % 26
            // 0. c     - Consider as text[count]-i
            // 1. c-i   - to start from 0 Number. eg. A -> 0, a->0.
            // 2. k     - to move position according to k.
            // 3. %26   - 26 letter in alphabatic lette. if > 26, get mod of 26.
            // 4. c+i   - to get back to ascii number.

            text[count] = ((((int)text[count] - i) + k) % 26) + i;
        }
    }

    return text;
}

bool isValid(string argv)
{
    for (int count = 0; count < strlen(argv); count++)
    {
        if (!isdigit(argv[count]))
        {
            return false;
        }
    }
    return true;
}