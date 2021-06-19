# Tideman
A program that runs a tideman voting for determining "Condorcet winner" who would have won any head-to-head matchup angainst another candidate.

## How it Works
The program uses a ranked-choice voting method called Tideman voting (also known as "ranked pairs"). By constructing a graph of candidates, Tideman voting method guaranteed to produce Condorcet winner of the election if one exists.

See more information [here](https://cs50.harvard.edu/x/2020/psets/3/tideman).

---

## How to Compile
    make tideman

## Usage
    Usage: tideman [candidate ...]

## Examples

Here's how the program will work if the election has `5` voters and 3 candidates (namely `Alice`, `Bob`, `Charlie`).

    $ ./tideman Alice Bob Charlie
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

    Charlie

The program will terminate if invalidate candidate was found during voting.

    $ ./tideman Alice Bob Charlie
    Number of voters: 5
    Rank 1: Alice
    Rank 2: Charlie
    Rank 3: Bob

    Rank 1: Alice
    Rank 2: Peter
    Invalid vote.