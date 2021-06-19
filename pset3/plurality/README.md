# Plurality
A program that runs a plurality election for determining the winner of election.

## How it works
The pluarality election follows a very simple method which is also known as "first-past-the-post" or "winner-take-all": every voter gets one vote, and the candidate with the most votes wins.

For more information, see [here](https://cs50.harvard.edu/x/2020/psets/3/plurality/).

---

## How to Compile
    make plurality

## Usage 
    Usage: plurality [candidate ...]

## Examples

Here's how the program should behave when the election has 3 voters and 2 candidates (named `Alice` and `Bob`).

    $ ./plurality Alice Bob
    Number of voters: 3
    Vote: Alice
    Vote: Bob
    Vote: Alice
    Alice

Here's how the program will work when the election has `5` voters and 3 candidates (named `Alice`, `Bob`, and `Charlie`).

According to the plurality vote, two candidates (`Alice` and `Bob`) will remain as a result which is a drawback of plurality voting.

    $ ./plurality Alice Bob Charlie
    Number of voters: 5
    Vote: Alice
    Vote: Charlie
    Vote: Bob
    Vote: Bob
    Vote: Alice
    Alice
    Bob

The program won't show the result until the voters vote the valid candidates who are on the list.

    $ ./plurality Alice Bob
    Number of voters: 3
    Vote: Alice
    Vote: Charlie
    Invalid vote.
    Vote: Alice
    Alice

