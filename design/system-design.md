# System Design
*This document describes the design used for section 3 of the project.*

Modules are:
- Memory
- Skeleton
- Simulator (stack-based, accumulator)

## Memory
Either three or five sections (his lecture indicated three, the project spec
indicated two):
- Data (variables and constants)
- Text (code of program)
- Stack (only used by stack-based simulator)

## Skeleton
Manages pieces that are shared by the two simulator types. Program counter,
initialization, UI. Loads a simulator and runs its commands.

## Simulator
Has a predefined instruction set architecture (ISA) based on its memory and
register implementation. There are two brands in this project: stack-based
and accumulator style.

### Stack-based simulator
Has the following instruction set:
- **PUSH X** which pushes the contents of memory at X onto the stack
- **POP Y** which pops the top element of the stack into memory Y
- **ADD** which removes the top two stack elements, adds them, and then stores
the result on top of the stack
- **MULT** which removes the top two stack elements, multiplies them, and then
stores the result on top of the stack
- **END** which ends the program.

Needs to read from stack, so needs to be aware where the top of the stack is
(TOS pointer).

### Accumulator simulator
Has the following instruction set:
- **LOAD X** which loads the contents of memory X into the accumulator
- **STO Y** which stores the value of the accumulator into memory Y
- **ADD X** which sums the value of memory X and the accumulator into the
accumulator
- **MULT X** which multiples the value of memory X and the accumulator into the
accumulator
- **END** which ends the program.

Only uses one register I guess? This seems just fine?
