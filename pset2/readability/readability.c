#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <cs50.h>

int letter, word, sentence;
string text;

void count_letter(char a);
void count_word(char a, char b);
void count_sentence(char a, char b);
void show_grade();

int main(void)
{
    text = "\0";

    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) <= 0);

    // Count letters, words, sentences
    for (int count = 0; count < strlen(text); count++)
    {
        count_letter(text[count]);
        count_word(text[count], text[count + 1]);
        count_sentence(text[count - 1], text[count]);
    }

    // Print grade
    show_grade();

}

// To Get Total Number of Letter in Text
void count_letter(char a)
{
    if (isalpha(a))
    {
        letter++;
    }
}

// To Get Total Number of Word in Text
void count_word(char a, char b)
{
    if ((!isspace(a)) && (isspace(b) || b == '\0'))
    {
        word++;
    }
}

// To Get Total Number of Sentence in Text
void count_sentence(char a, char b)
{
    if ((isalpha(a)) && (b == '.' || b == '?' || b == '!'))
    {
        sentence++;
    }
}


void show_grade()
{
    // Grade = 0.0588 * L - 0.296 * S - 15.8
    int result = round((0.0588 * (100 * (float)letter / (float)word)) - (0.296 * (100 * (float)sentence / (float)word)) - 15.8);

    if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (result > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", result);
    }

}

