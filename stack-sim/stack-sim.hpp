#include "../memory/memory.hpp"

#define X_ADDR 256
#define Y_ADDR 257
#define Z_ADDR 258

#ifndef STACK_SIM_H
#define STACK_SIM_H

class StackSim {
private:
  int sp = -1; /* Stack pointer */

  /*
    Ints a and b are addresses.
  */
#ifndef TEST
  Memory m;

  bool push(int a);
  bool pop();
  bool add(int a, int b);
  bool mul(int a, int b);
  bool end();
#endif

public:
  void run();

  #ifdef TEST
    Memory m;
    
    bool push(int a);
    bool pop();
    bool add(int a, int b);
    bool mul(int a, int b);
    bool end();
  #endif
};

#endif
