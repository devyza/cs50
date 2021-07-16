#!/usr/bin/env python

from sys import argv, exit
from cs50 import SQL
import csv
import errno


def main():

    # Check whether input is CSV or not.
    if len(argv) != 2 or argv[1][-4:] != ".csv":
        print("Usage: python import.py data.csv")
        exit(1)

    # Setting up database connection
    db_con = SQL("sqlite:///students.db")

    try:
        # Reading csv file
        with open(argv[1], 'r') as importFile:
            reader = csv.DictReader(importFile)

            # Read data line by line
            for row in reader:
                fullName = row['name'].split()
                middle = fullName[1:-1]

                # Check if middle name is empty or not
                if not middle:
                    middle = None

                # Save into database
                db_con.execute("INSERT INTO students (first, middle, last, house, birth) " +
                               "VALUES(?, ?, ?, ?, ?)",
                               fullName[0], middle, fullName[-1], row['house'], row['birth'])

    except FileNotFoundError:
        print("File Not Found")

        # Return Error Code as Stderr (2)
        exit(errno.ENOENT)

    exit(0)


if __name__ == '__main__':
    main()