SPAM is MAPS spelled backwards.

Spam
====
COMP 4300 Computer Architecture
Dr. Qin
Jacob Harris (Jake) (jch0039) & Clayton Miller (Clay) (cdm0025)
Project 2


Compilation
===========
Our program is called spam.
To build our program, run `make`.
To build our tests, run `make test`.

Usage
=====
To run the general purpose register simulator, run `./spam gpr palindrome.s`.
To run our tests, run `make travis`.


Design Issues
=============
* C++ doesn't have a method that splits a string by a delimeter and stores the
output in a vector, so I added one.

* We thought we had to programatically swap labels with addresses, so we wrote
code to do that. Turns out we could have manually swapped them when we rewrote
the assembly file.

* We originally wrote code to access memory chunk by chunk instead of byte by
byte--that came back to byte us.
