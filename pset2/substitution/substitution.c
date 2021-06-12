#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

string request_input(string dispalytext);
string substitution(string text, string cipher);
bool isValid(int argc, string argv[]);
bool isDuplicate(string cipher);

int main(int argc, string argv[])
{

    if (isValid(argc, argv))
    {
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        // Get return value from request_input() function
        string plaintext = request_input("plaintext: ");

        // Print Output
        printf("ciphertext: %s\n", substitution(plaintext, argv[1]));
        return 0;
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    return 0;
}

// Function to get string from user input
//     - If user input is empty the function will
//       automitically request again
string request_input(string displaytext)
{
    string text = "\0";
    do
    {
        text = get_string("%s", displaytext);
    }
    while (strlen(text) <= 0);
    return text;
}

// Fuction for substitution of the plain text
// 0. Starting from index 0 of plaintext, all letters
//    from the plaintext will be replaced as stated by
//    the cipher.
// 1. Get the value from text[count]        -> B (66)
// 2. Get the value from cipher array
//      - If text[count] is in UPPER case,  -> 66-65 = 0
//        minus A (65) to get index value of
//        cipher array
//      - If not, minux a (95)
// 3. Replace the value of cipher array to plantext
string substitution(string text, string cipher)
{
    int i = 0;

    for (int count = 0; count < strlen(text); count++)
    {
        if (isalpha(text[count]))
        {
            if (isupper(text[count]))
            {
                i = toupper(cipher[(int)text[count] - 65]);
            }
            else
            {
                i = tolower(cipher[(int)text[count] - 97]);
            }

            text[count] = i;
        }
    }
    return text;
}

// Function to check whether the usage is valid or not.
// 1. If the argument count is not 2, it will return false.
// 2. If the cipher is duplicated with multiple characters,
//    it will return false.
bool isValid(int argc, string argv[])
{
    if (argc == 2 && isDuplicate(argv[1]))
    {
        for (int count = 0; count < strlen(argv[1]); count++)
        {
            if (!isalpha(argv[1][count]))
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

// Function to check whether the cipher is
// duplicated with muiplicated characters or not
bool isDuplicate(string cipher)
{
    int count = 0;
    for (int i = 0; i < strlen(cipher); i++)
    {
        for (int j = i + 1; j < strlen(cipher); j++)
        {
            if (cipher[i] == cipher[j])
            {
                return false;
            }
        }
    }
    return true;
}