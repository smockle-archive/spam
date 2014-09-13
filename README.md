[![Build Status](https://travis-ci.org/smockle/spam.svg?branch=master)](https://travis-ci.org/smockle/spam)

SPAM is MAPS spelled backwards.


Spam
====
COMP 4300 Computer Architecture
Dr. Qin
Jacob Harris (Jake) (jch0039) & Clayton Miller (Clay) (cdm0025)
Project 1


Compilation
===========
Our program is called spam.
To build our program, run `make spam`.
To build our tests, run `make test`.


Usage
=====
To run the accumulator simulator, run `./spam accumulator accumulator/quadratic_eval.s`.
To run the stack simulator, run `./spam stack stack/quadratic_eval.s`.
To run our tests, run `make travis`.


Design Issues
=============
* C++ doesn't have trim or tolower functions in std::string. This was surprising and
required a couple extra functions.

* Our original memory implementation could only store one thing at a time. We discovered
this late and had to do some refactoring.

* C++ segfaults (with no stack trace or anything useful for debugging) when you address
anything outside of an array, or access anything undecalared. This cost us lots of time
#debugging.

* We had lots of issues with including the correct header files and with setting up our
Makefile properly. We added #ifndef TEST in several places to prevent duplicate main
functions. We added references to cpp files to the Makefile to prevent missing symbol
errors.

* The version of g++ on Travis CI was 4.6, which caused errors (we were using 4.8). We
had to figure out how to install g++ 4.8 in the Travis CI environment.
