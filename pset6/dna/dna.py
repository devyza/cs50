from csv import DictReader
from sys import argv


def main():

    if len(argv) < 3 or argv[1][-4:] != ".csv" or argv[2][-4:] != ".txt":
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Get DNA sequence for sequence file
    with open(argv[2], 'r') as sequenceFile:
        sequence = sequenceFile.read().strip()

    # Reading Database File
    database = open(argv[1])
    data = DictReader(database)
    headers = data.fieldnames[1:]

    # Assign dictionary list for total number of STR
    counts = {}

    # Count longest number of STR
    for i in headers:
        counts[i] = countSTR(sequence, i)

    # Find and print person
    for row in data:

        # Using list comprehension and all() which returns true/false
        # Reference: https://www.programiz.com/python-programming/list-comprehension
        if (all(int(row[header]) == counts[header] for header in headers)):
            print(row['name'])
            database.close()
            exit(0)

    # If Not Found Error
    print("No Match")
    database.close()


# Count the longest number of STR
def countSTR(sequence, sub):

    # Longest Number of STR repeat
    longestSTR = 0

    # Length of STR
    length = len(sub)

    i = 0
    while i < len(sequence):
        count = 0
        # Skip by the length of the subsequence, if they are the same
        while sequence[i: i + length] == sub:
            count += 1
            i += length
        else:
            i += 1
        # If the greter number was found
        longestSTR = max(count, longestSTR)
    return longestSTR


if __name__ == "__main__":
    main()