# DNA

A program that identifies a person based on their DNA and output to whom the DNA (mostl likely) belongs.

DNA is a sequence of molecules called nucleotides. Each nucleotide of DNA contains one of four different bases:

* A - Acytosine
* C - Cytosine
* G - Guanine
* T - Thymine

One place where DNA tends to have high genetic diversity is in Short Tandem Repeats(SRTS). An STR is a short sequence of DNA bases that tend to repeat.

    Alice: CTAGATAGATAGATAGATGACTA
    Bob  : CTAGATAGATAGATAGATAGATT
>
    Alice: CT|AGAT|AGAT|AGAT|AGAT|GACT|A
    Bob  : CT|AGAT|AGAT|AGAT|AGAT|AGAT|T

See more informateion [here](https://cs50.harvard.edu/x/2020/psets/6/dna).

---

## Usage
    Usage: python dna.py data.csv sequence.txt

## Example

The program might work if the STR counts match exactly with any of the individuals in the `CSV` file.

    $ python dna.py databases/small.csv sequences/1.txt
    Bob

The program will output `No Match` if the STR counts doesn't match with any of the individual in the `CSV` file.

    $ python dna.py databases/large.csv sequences/16.txt
    No match

This program should behave if the use enters with invalid inputs.

    $ python dna.py
    Usage: python dna.py data.csv sequence.txt
    $ python dna.py data.csv
    Usage: python dna.py data.csv sequence.txt