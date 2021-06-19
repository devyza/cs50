# Runoff
A program that runs a runoff election for determining the winner of election.

## How it Works
Unlike plurality vote, the program runs another system known as "Ranked-choice Voting System": voters can vote for more than one candidate, and they can ran the candidates in order of preference instead of voting for their top choice.

For more information, see [here](https://cs50.harvard.edu/x/2020/psets/3/runoff).

---

## How to Compile
    make runoff

## Usage
    Usage: runoff [candidate ...]

## Examples

Here's how the program will work when the election has `5` voters and 3 candidates (named `Alice`, `Bob`, and `Charlie`).

    $ ./runoff Alice Bob Charlie
    Number of voters: 5
    Rank 1: Alice
    Rank 2: Charlie
    Rank 3: Bob

    Rank 1: Alice
    Rank 2: Charlie
    Rank 3: Bob

    Rank 1: Bob
    Rank 2: Charlie
    Rank 3: Alice

    Rank 1: Bob
    Rank 2: Charlie
    Rank 3: Alice

    Rank 1: Charlie
    Rank 2: Alice
    Rank 3: Bob

    Alice

The program will stop immediately if the invalid vote was found.

    $ ./runoff Alice Bob Charlie
    Number of voters: 5
    Rank 1: Alice
    Rank 2: Charlie
    Rank 3: Bob

    Rank 1: Bob
    Rank 2: Peter
    Invalid vote.