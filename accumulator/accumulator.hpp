#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#import "../skeleton/skeleton.hpp"
#import <regex>

class Accumulator {
  int a;

  Accumulator(Memory memory);
  int load(int address);
  int store(int address);
  int add(int address);
  int multiply(int address);
  int end();
};

#endif
