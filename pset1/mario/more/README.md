# Mario (more)
A program to create 2 pyramids in text, using hashes (#) for bricks.

See more instructions [here](https://cs50.harvard.edu/x/2020/psets/1/mario/more)

---
## How to Compile
    $ make mario

## Examples
 > :warning: Note: Height of the pyramid should be a positive integer between 1 and 8.

Here is how the program might if the user inputs is `3`.

    $ ./mario
    Height: 3
      # #
     ## ##
    ### ###

If the user doesn’t, in fact, input a positive integer between 1 and 8, inclusive, when prompted, the program should re-prompt the user until they cooperate:

    $ ./mario
    Height: -1
    Height: 0
    Height: 42
    Height: 50
    Height: 4
        #  #
       ##  ##
      ###  ###
     ####  ####