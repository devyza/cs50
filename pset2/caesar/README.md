# Caesar

 A program that encrypts messages using Caesar’s cipher.

 See more instructions [here](https://cs50.harvard.edu/x/2020/psets/2/caesar/)

---

## How to Compile
    $ make caesar

## Usage
    Usage: ./caesar key

## Examples
Here is how the program will work if the user inputs a key of `2` and a plaintext of `Hello World`.

    $ ./caesar 2
    Plain Text: Hello World
    ciphertext: Jgnnq Yqtnf

The program won't work if the user doesn't follow the usage of the program.

    $ ./caesar 1 2 3
    Usage: ./caesar key
    $ ./caesar HELLO
    Usage: ./caesar key
    $ ./caesar
    Usage: ./caesar key