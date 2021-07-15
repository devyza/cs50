# Readability (Python)
A program written in Python to computer approximate grade level needed to comprehend some text.

**Formula of Coleman-Liau Index**

    index = 0.0588 * L - 0.296 * S - 15.8

    L = The average number of letters per 100 words in the text
    S = The average number of sentences per 100 words

See more information [here](https://cs50.harvard.edu/x/2020/psets/6/readability).

---

## Usage
    $ python3 readability.py

## Example

    $ python readability.py
    Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
    Grade 3