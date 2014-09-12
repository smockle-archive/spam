#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include "../skeleton/skeleton.hpp"
#include <regex>

namespace spam {
  class Accumulator {
    public:
      int a;
      Memory * memory;

      Accumulator(Memory * mp);
      int load(int address);
      int store(int address);
      int add(int address);
      int multiply(int address);
      int end();
  };
}

#endif
