#ifndef STACK_H
#define STACK_H

#include "../utilities.hpp"
#include "../memory/memory.hpp"

class Stack {
public:
  int sp = -1; // stack pointer
  Memory m;

  Stack();
  Stack(Memory * mp);

  bool push(int a);
  bool pop (int a);
  bool add ();
  bool mul ();
  bool end ();

  int run();
};

#endif
