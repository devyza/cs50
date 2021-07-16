from sys import exit, argv
from cs50 import SQL


def main():

    # Checking user input
    if len(argv) != 2:
        print("Invalid")

    # Connecting SQL connection
    db_con = SQL("sqlite:///students.db")

    # Database Query
    rows = db_con.execute(f"SELECT * FROM students WHERE house = '{argv[1]}' ORDER BY last")

    for row in rows:

        # Checking middle is exist or not
        if row['middle'] != None:
            fullName = f"{row['first']} {row['middle']} {row['last']}"
        else:
            fullName = f"{row['first']} {row['last']}"

        # STDOUT
        print(f"{fullName}, born {row['birth']}")

    exit(0)


if __name__ == "__main__":
    main()
