#ifndef SKELETON_H
#define SKELETON_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "../utilities.hpp"
#include "../memory/memory.hpp"
#include "../stack/stack.hpp"
#include "../accumulator/accumulator.hpp"

namespace spam {
  class Skeleton {
    public:
      Memory * memory = new Memory();

      bool file_exists(std::string filename);
      int do_memory(std::string filename);
      int do_stack(int argc, char** argv);
      int do_accumulator(int argc, char** argv);
      int do_gpr(int argc, char** argv);
      int do_help();
  };
}

#endif
