#include "../utilities.hpp"
#include "../memory/memory.hpp"

class Stack {
public:
  int sp = -1; // stack pointer
  Memory m;

  bool push(int a);
  bool pop (int a);
  bool add ();
  bool mul ();
  bool end ();

  void run();
};
