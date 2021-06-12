# Readability
A program written in C to compute the approximate grade level needed to comprehend some text and messages with the use of Coleman-Liau index.

Formula of Coleman-Liau index is

    index = 0.0588 * L - 0.296 * S - 15.8

    L = The average number of letters per 100 words in the text
    S = The average number of sentences per 100 words

See more instructions [here](https://cs50.harvard.edu/x/2020/psets/2/readability) 

---

## How to Compile
    $ make readability

## Examples

Here is how the program will work when the text the user inputed has 29 letters, 4 sentences, and 8 words.

    $ ./readability
    One fish. Two fish. Red fish. Blue fish.
    Grade 1

This is another example, when the text has 65 letters, 4 sentences, and 14 words.

    $ ./readability
    Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
    Grade 3