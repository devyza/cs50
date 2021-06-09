# Cash
A program that asks the user how much change is owned and then prints the minimum number of coins with the help of greedy algorithm.

See more instructions [here](https://cs50.harvard.edu/x/2020/psets/1/cash/)

---
## How to Compile
    $ make cash 
    
## Examples

Here is how the program might if the user inputs is `0.41`.

    $ ./cash
    Change owed: 0.41
    4

The program should behave as below if the input is invalid.

    $ ./cash
    Change owed: -0.41
    Change owed: foo
    Change owed: 0.41
    4