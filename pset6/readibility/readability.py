from cs50 import get_string


def main():

    # Get Text from Standard Input
    text = None
    while text == None:
        text = get_string("Text: ")
    text = text.split()

    letter = word = sentence = 0
    for w in text:

        # Count Word
        word += 1

        # Count Letter
        for c in w:
            if c.isalpha():
                letter += 1

        # Count Sentence
        if (w[-1] == "." or w[-1] == "?" or w[-1] == "!"):
            sentence += 1

    result = coleman_index(letter, word, sentence)

    if result < 1:
        print("Before Grade 1")
    elif result > 16:
        print("Grade 16+")
    else:
        print(f"Grade {result}")


# Coleman Liau Index (Grade = 0.0588 * L - 0.296 * S - 15.8)
# L = 100 * letter / word (The average number of letters per 100 words)
# S = 100 * sentence / word (The average number of sentences per 100 words)

def coleman_index(letter, word, sentence):
    return round((0.0588 * (100 * letter / word)) - (0.296 * (100 * sentence / word)) - 15.8)


if __name__ == "__main__":
    main()