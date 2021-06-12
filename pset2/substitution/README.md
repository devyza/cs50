# Substitution
A program written in C to implement a substitution cipher.

See more information [here](https://cs50.harvard.edu/x/2020/psets/2/substitution).

---
## How to Compile
    $ make substitution

## Usage
    Usage: ./substitution key

## Examples

Here is how the program will work if the user inputs a key of `YTNSHKVEFXRBAUQZCLWDMIPGJO` and a plaintext of `HELLO`.

    $ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
    plaintext:  hello, world
    ciphertext: jrssb, ybwsp

> :warning: Notice that neither the comma nor the space were substituted by the cipher. Only substitute alphabetical characters!

> :warning: Notice, too, that the case of the original message has been preserved. Lowercase letters remain lowercase, and uppercase letters remain uppercase.

Here is how the program will work if user doesn't provide a valid key.

    $ ./substitution ABC
    Key must contain 26 characters.

The program will behave as below if the user inputs invalid key.

    $ ./substitution
    Usage: ./substitution key
    $ ./substitution 1 2 3
    Usage: ./substitution key