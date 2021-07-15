# Mario: less (Python)
A program written in python to print out a half-pyramid of a specified height.

See more information [here](https://cs50.harvard.edu/x/2020/psets/6/mario/less).

---

## Usage
    $ python3 mario.py

## Examples

 > :warning: Note: Height of the pyramid should be a positive integer between 1 and 8.

Here is how the program might if the user inputs is `3`.

    $ python3 mario.py
    Height: 3
      #
     ##
    ###

If the user doesn’t, in fact, input a positive integer between 1 and 8, inclusive, when prompted, the program should re-prompt the user until they cooperate:

    $ python3 mario.py
    Height: -1
    Height: 0
    Height: 42
    Height: 50
    Height: 4
       #
      ##
     ###
    ####